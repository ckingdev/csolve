package main

import (
	"github.com/go-martini/martini"

	"errors"
	"flag"
	"fmt"
	"io"
	"net/http"
	"os"
	"os/exec"
	"strconv"
)

const version = "0.0.1-alpha" // semvar versioning?
const debug = true
const pipeBufLength = 100

var pruneDepth int

func init() {
	flag.IntVar(&pruneDepth, "d", 7, "how deep of a pruning table to use")

	// Check that the binary exists
	if _, err := os.Stat("../build/2x2server"); os.IsNotExist(err) {
		panic(errors.New("No binary found!"))
	}
}

func gen2x2PruningTable(depth int) error {
	depthStr := strconv.Itoa(depth)
	savePath := "2x2_d" + depthStr + ".prun"

	//Check if pruning table already exists
	if _, err := os.Stat(savePath); !os.IsNotExist(err) {
		fmt.Println("Pruning table already generated.")
		return nil
	}

	cmd := exec.Command("../build/2x2server", depthStr, savePath)
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
	flag.Parse()

	f, err := io

	err := gen2x2PruningTable(pruneDepth)
	if err != nil {
		panic(err)
	}

	m := martini.Classic()

	m.Get("/", func() (int, string) {
		return http.StatusTeapot, "Tea time!"
	})

	m.Run()
}
