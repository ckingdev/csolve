package main

import (
	"io/ioutil"
	"net/http"
	"testing"
)

func TestServerRunning(t *testing.T) {
	resp, err := http.Get("http://localhost:3000/ping")
	if err != nil {
		t.Fatalf("Request failed with error: %v", err.Error())
	}
	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		t.Fatalf("Body read failed with error: %v", err.Error())
	}
	if resp.StatusCode != http.StatusOK {
		t.Fatalf("Bad status code, expected 200, got %v", resp.StatusCode)
	}
	if string(body) != "pong" {
		t.Fatalf("Incorrect response, expected 'pong', got: '%v'", string(body))
	}
}
