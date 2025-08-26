package main

import (
	"fmt"
	"time"
)


var res = 9
var value = 32

func main() {
	var goChan = make(chan int)
	var mainChan = make(chan string)

	go calculateSquare(value, goChan)
	go printResult(goChan, mainChan)

	<- mainChan
}

func calculateSquare(value int, goChan chan int) {
	fmt.Println("Calculating for 3 seconds")
	time.Sleep(time.Second*3)
	res = value*value
	goChan <- res
}

func printResult(goChan chan int, mainChan chan string) {
	time.Sleep(time.Second*1)
	fmt.Println("Ther result of ", value, " squared is ", <- goChan)
	mainChan <- "You can quit now"
}