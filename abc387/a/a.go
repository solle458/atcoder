package main

import (
	"fmt"
	"math"
)

func main() {
	var a, b int
	fmt.Scan(&a, &b)
	p := float64(a + b)
	fmt.Println(int(math.Pow(p, 2)))
}
