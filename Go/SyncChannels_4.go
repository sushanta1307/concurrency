package main

import (
	"fmt"
	"sync"
	"time"
)

func main() {
	var wg sync.WaitGroup

	for i:=1; i<=10000; i++ {

		wg.Add(1)

		go func(j int) {
			var goChan = make(chan int)
			var mainChan = make(chan string)

			var res int

			calculateSquare := func() {
				time.Sleep(time.Second*3)
				res = j*j
				goChan <- res
			}

			var printResult = func() {
				fmt.Println(j, " squared is ", <- goChan)
				mainChan <- "You can quit now"
			}

			go calculateSquare()
			go printResult()

			<- mainChan
			wg.Done()
		} (i)
	}

	wg.Wait()
}