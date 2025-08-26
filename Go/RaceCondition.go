package main

import (
	"fmt"
	"sync"
	// "sync/atomic"
)

var (
	wg = sync.WaitGroup{}
	mu = sync.Mutex{}
	cv = sync.NewCond(&mu)

	inventory int32 = 1000
)

func main() {
	fmt.Println("Starting Inventory --", inventory)

	wg.Add(2)

	go sale()
	go buy()

	wg.Wait()

	fmt.Println("Starting Inventory --", inventory)
}

func sale() {
	for i:=1;i<3000;i++ {
		mu.Lock()
		for inventory - 100 < 0 {
			cv.Wait()
		}
		inventory -= 100
		mu.Unlock()
	}
	wg.Done()
}
func buy() {
	for i:=1;i<3000;i++ {
		mu.Lock()
		inventory += 100
		cv.Signal()
		mu.Unlock()
		// atomic.AddInt32(&inventory, 100)
	}
	wg.Done()
}
