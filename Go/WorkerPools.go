package main

import (
	"fmt"
	"time"
)


func main() {
	const numJobs int = 10
	var jobsChan = make(chan int, numJobs)
	var jobsCompletedChan = make(chan int)

	for w:=1;w<=3;w++ {
		go worker(w, jobsChan, jobsCompletedChan)
	}

	for j:=1;j<=numJobs;j++ {
		jobsChan <- j
	}

	// channel closed for write
	// still can be read
	close(jobsChan)

	for a:=1;a<=int(numJobs);a++ {
		<- jobsCompletedChan
	}
}

func worker(id int, jobsChan <-chan int, jobsCompletedChan chan <- int) {
	// jobsChan can be read only
	// jobsCompletedChan can be written only

	for j := range jobsChan {
		fmt.Println("worker ", id, " started job ", j, ". Left Jobs ", len(jobsChan))
		time.Sleep(time.Second*2)
		fmt.Println("Worker ", id, " completed ", j)
		jobsCompletedChan <- j
	}
}