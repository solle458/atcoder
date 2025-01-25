package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	R := bufio.NewReader(os.Stdin)
	W := bufio.NewWriter(os.Stdout)
	defer W.Flush()

	var h, w int
	fmt.Fscan(R, &h)
	fmt.Fscan(R, &w)
	s := make([]string, h)
	for i := 0; i < h; i++ {
		fmt.Fscan(R, &s[i])
	}
	maxX, minX, maxY, minY := -1, int(1e9), -1, int(1e9)
	for i := 0; i < h; i++ {
		for j := 0; j < w; j++ {
			if s[i][j] == '#' {
				Max(&maxY, i)
				Min(&minY, i)
				Max(&maxX, j)
				Min(&minX, j)
			}
		}
	}
	for i := minY; i <= maxY; i++ {
		for j := minX; j <= maxX; j++ {
			if s[i][j] == '.' {
				fmt.Fprintln(W, "No")
				return
			}
		}
	}
	fmt.Fprintln(W, "Yes")
}

func Max[T int | float64 | string](a *T, b T) bool {
	if *a < b {
		*a = b
		return true
	} else {
		return false
	}
}

func Min[T int | float64 | string](a *T, b T) bool {
	if *a > b {
		*a = b
		return true
	} else {
		return false
	}
}
