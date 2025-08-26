package main

import (
	"fmt"
	"sync"
	"time"
)

// define the wait group
var wg = sync.WaitGroup{}

func main() {
	start := time.Now()

	// add the number of go routines to wait for
	wg.Add(2)

	go doSomething()
	go doSomethingElse()

	// wait for the go routines to finish
	wg.Wait()

	fmt.Println("I am done")
	elapsed := time.Since(start)
	fmt.Println("Processes took ", elapsed)
}

func doSomething() {
	time.Sleep(time.Second*2)
	fmt.Println("I have done something")
	wg.Done()
}

func doSomethingElse() {
	time.Sleep(time.Second*3)
	fmt.Println("I have done something else")
	wg.Done()
}