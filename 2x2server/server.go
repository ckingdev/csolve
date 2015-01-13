package main

import (
	"github.com/go-martini/martini"

	"flag"
	"fmt"
	"log"
	"net/http"
	"os"
	"os/exec"
	"strconv"
)

const version = "0.0.1-alpha"
const logPath = "log"

var pruneDepth int
var logger *log.Logger

func init() {
	flag.IntVar(&pruneDepth, "d", 7, "how deep of a pruning table to use")
}

func gen2x2PruningTable(depth int) error {
	depthStr := strconv.Itoa(depth)
	savePath := "2x2_d" + depthStr + ".prun"

	//Check if pruning table already exists
	if _, err := os.Stat(savePath); !os.IsNotExist(err) {
		logger.Println("Pruning table already generated.")
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

	// open log file
	var err error
	var f *os.File
	// check if log file already exists
	if _, existsErr := os.Stat(logPath); os.IsNotExist(existsErr) {
		f, err = os.Create(logPath)
	} else {
		f, err = os.OpenFile(logPath, os.O_RDWR|os.O_APPEND, 0660)
	}
	if err != nil {
		fmt.Println(err.Error())
		os.Exit(1)
	}
	defer f.Close()
	logger = log.New(f, "["+version+"] ", log.LstdFlags)

	// Check that the binary exists
	if _, err := os.Stat("../build/2x2server"); os.IsNotExist(err) {
		logger.Fatalln("No binary found!")
	}

	err = gen2x2PruningTable(pruneDepth)
	if err != nil {
		panic(err)
	}

	m := martini.Classic()

	m.Get("/", func() (int, string) {
		return http.StatusTeapot, "Tea time!"
	})

	m.Run()
}
