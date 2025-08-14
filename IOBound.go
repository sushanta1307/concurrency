package main

import (
	"fmt"
	"net/http"
	"runtime"
	"sync"
	"time"
)

var wg sync.WaitGroup

func main() {

	runtime.GOMAXPROCS(8)
	fmt.Println(runtime.NumCPU())

	
	links := []string {
		"http://golang.org", 
		"http://google.com",
		"http://medium.com",
		"http://github.com",
		"http://sushsena.in",
		"http://facebook.com",
	}

	wg.Add(len(links))

	start := time.Now()

	for _, link := range links {
		go checkLink(link)
	}

	wg.Wait()

	fmt.Println("It took ", time.Since(start))
}

func checkLink(link string) {
	_, err := http.Get(link)

	if err != nil {
		fmt.Println(link, "not responding --", err)
		return
	}

	fmt.Println(link, " is active")
	wg.Done()
}