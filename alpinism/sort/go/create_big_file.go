package main

import (
	"bufio"
	"fmt"
	"math"
	"math/rand"
	"os"
	"strconv"
	"time"
)

func mainBak() {
	var max = int(math.Pow(10, 8)) * 10
	f, err := os.OpenFile("./number_data.txt", os.O_CREATE|os.O_APPEND|os.O_RDWR, os.ModePerm)
	if err != nil {
		fmt.Println(err)
		os.Exit(0)
	}
	defer f.Close()
	writer := bufio.NewWriterSize(f, int(math.Pow(2, 30)))
	for i := 0; i < max; i++ {
		rand.Seed(time.Now().UnixNano())
		tmpNum := rand.Intn(max)
		writer.WriteString(strconv.Itoa(tmpNum) + "\n")
	}
	writer.Flush()
}
