package main

import (
	"fmt"
	"sync"
	"time"
)


var res = 9
var value = 32

func main() {
	var wg sync.WaitGroup

	wg.Add(1)

	go func() {
		var goChan = make(chan int)
		var mainChan = make(chan string)

		calculateSquare := func() {
			fmt.Println("Calculating for 3 seconds")
			time.Sleep(time.Second*3)
			res = value*value
			goChan <- res
		}

		var printResult = func() {
			fmt.Println("Ther result of ", value, " squared is ", <- goChan)
			mainChan <- "You can quit now"
		}

		go calculateSquare()
		go printResult()

		<- mainChan
		wg.Done()
	} ()

	wg.Wait()
}