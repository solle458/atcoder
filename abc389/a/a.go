package main

import (
	"fmt"

	"github.com/solle458/atcoder/tree/main/lib/go/LazySegtree.go"
)

func main() {
	fmt.Println("Hello, World!")
	seg := LazySegtree.NewLazySegtree([]int{1, 2, 3, 4}, func(a, b int) int { return a + b }, func() int { return 0 }, func(f, x int) int { return f + x }, func(f, g int) int { return f + g }, func() int { return 0 })
}
