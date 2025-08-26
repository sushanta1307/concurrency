package main

import (
	"fmt"
	"runtime"
	"sync"
	"time"
)

var wg sync.WaitGroup	

func main() {
	fmt.Println(runtime.GOMAXPROCS(0))
	runtime.GOMAXPROCS(4 )


	start := time.Now()

	wg.Add(6)

	go counta()
	go countb()
	go countc()
	go countd()
	go counte()
	go countf()

	wg.Wait()

	fmt.Println("Time taken: ", time.Since(start))
}

func counta() {
	fmt.Println("AAA starting...")
	for i:=1;i<=10_000_000_000;i++ {

	}
	fmt.Println("AAA completed")
	wg.Done()
}
func countb() {
	fmt.Println("BBB starting...")
	for i:=1;i<=10_000_000_000;i++ {
		
	}
	fmt.Println("BBB completed")
	wg.Done()
}
func countc() {
	fmt.Println("CCC starting...")
	for i:=1;i<=10_000_000_000;i++ {
		
	}
	fmt.Println("CCC completed")
	wg.Done()
}
func countd() {
	fmt.Println("DDD starting...")
	for i:=1;i<=10_000_000_000;i++ {
		
	}
	fmt.Println("DDD completed")
	wg.Done()
}
func counte() {
	fmt.Println("EEE starting...")
	for i:=1;i<=10_000_000_000;i++ {
		
	}
	fmt.Println("EEE completed")
	wg.Done()
}
func countf() {
	fmt.Println("FFF starting...")
	for i:=1;i<=10_000_000_000;i++ {
		
	}
	fmt.Println("FFF completed")
	wg.Done()
}
