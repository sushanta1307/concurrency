package main

import (
	"fmt"
	"runtime"
	"time"
)	

func main() {
	fmt.Println(runtime.GOMAXPROCS(0))
	runtime.GOMAXPROCS(8)

	c := make(chan string)

	start := time.Now()

	go counta(c)
	go countb(c)
	go countc(c)
	go countd(c)
	go counte(c)
	go countf(c)

	for i:=1;i<=6;i++ {
		fmt.Println(<- c)
	}

	fmt.Println("Time taken: ", time.Since(start))
}

func counta(c chan string) {
	fmt.Println("AAA starting...")
	for i:=1;i<=10_000_000_000;i++ {

	}
	c <- "AAA completed"
}
func countb(c chan string) {
	fmt.Println("BBB starting...")
	for i:=1;i<=10_000_000_000;i++ {
		
	}
	c <- "BBB completed"
}
func countc(c chan string) {
	fmt.Println("CCC starting...")
	for i:=1;i<=10_000_000_000;i++ {
		
	}
	c <- "CCC completed"
}
func countd(c chan string) {
	fmt.Println("DDD starting...")
	for i:=1;i<=10_000_000_000;i++ {
		
	}
	c <- "DDD completed"
}
func counte(c chan string) {
	fmt.Println("EEE starting...")
	for i:=1;i<=10_000_000_000;i++ {
		
	}
	
	c <- "EEE completed"
}
func countf(c chan string) {
	fmt.Println("FFF starting...")
	for i:=1;i<=10_000_000_000;i++ {
		
	}
	c <- "FFF completed"
}
