package main

import (
	"errors"
	"github.com/go-martini/martini"
	"io"
	"net/http"
	"os/exec"
)

const version = "0.0.1-alpha" // semvar versioning?
const debug = true
const pipeBufLength = 100

func usage() (int, string) {
	return http.StatusOK, "to do"
}

func errorOnPipeRead(pipe io.Reader) error {
	buf := make([]byte, 1)
	nRead, err := pipe.Read(buf)
	if nRead > 0 {
		return errors.New("Compilation error.")
	}
	if err != nil && err.Error() != "EOF" { // EOF is expected
		return err
	}
	return nil
}

func getStdOutErr(cmd *exec.Cmd) (io.Reader, io.Reader, error) {
	stdout, err := cmd.StdoutPipe()
	if err != nil {
		return nil, nil, err
	}
	stderr, err := cmd.StderrPipe()
	if err != nil {
		return nil, nil, err
	}
	return stdout, stderr, nil
}

func compile(cmd *exec.Cmd) error {
	// Make sure we can open pipes
	stdout, stderr, err := getStdOutErr(cmd)
	if err != nil {
		return err
	}

	// Check that command starts ok
	err = cmd.Start()
	if err != nil {
		return err
	}

	// Shouldn't have output if the compilation succeeds - error if there is
	err = errorOnPipeRead(stdout)
	if err != nil {
		return err
	}
	err = errorOnPipeRead(stderr)
	if err != nil {
		return err
	}

	// Check that command ran with exit code 0
	err = cmd.Wait()
	if err != nil {
		return err
	}

	return nil
}

func compileHandler() (int, string) {
	cmd := exec.Command("clang++", "test.cpp")
	err := compile(cmd)
	if err != nil {
		return http.StatusInternalServerError, err.Error()
	}
	return http.StatusOK, "Success!"
}

func gen2x2PruningTable(depth string, savePath string) error {
	cmd := exec.Command("../build/2x2server", depth, savePath)

	err := cmd.Start()
	if err != nil {
		return err
	}

	err = cmd.Wait()
	if err != nil {
		return err
	}
	return nil
}

func main() {
	// for 'solve' function just pass concatenated list of 0-9
	m := martini.Classic()

	err := gen2x2PruningTable("7", "2x2_d7.prune")
	if err != nil {
		panic(err)
	}

	m.Get("/", usage)

	m.Get("/version", func() string {
		return version + "\n"
	})

	m.Get("/compile", compileHandler)

	m.Run()
}
