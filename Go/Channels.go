package main

import (
	"fmt"
	"time"
)

var ch = make(chan string)

func main() {
	start := time.Now()

	go doSomething()
	go doSomethingElse()

	fmt.Println(<- ch)
	fmt.Println(<- ch)

	fmt.Println("I am done")
	elapsed := time.Since(start)
	fmt.Println("Processes took ", elapsed)


	var ch1 = make(chan string, 2)
	ch1 <- "Hello "
	ch1<- "World"

	fmt.Printf(<- ch1)
	fmt.Println(<- ch1)
}

func doSomething() {
	time.Sleep(time.Second*2)
	fmt.Println("I have done something")
	ch <- "doSomething finished \n\n"
}

func doSomethingElse() {
	time.Sleep(time.Second*3)
	fmt.Println("I have done something else")
	ch <- "doSomethingElse finished \n\n"
}
