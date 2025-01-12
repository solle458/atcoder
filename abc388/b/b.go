package main

import "fmt"

func Max[T int | float64 | string](a, b *T) bool {
	if *a < *b {
		*a = *b
		return true
	} else {
		return false
	}
}

func main() {
	var n, d int
	fmt.Scan(&n, &d)
	t, l := make([]int, n), make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&t[i], &l[i])
	}
	for i := 1; i <= d; i++ {
		ans := 0
		for j := 0; j < n; j++ {
			tmp := t[j] * (i + l[j])
			Max(&ans, &tmp)
		}
		fmt.Println(ans)
	}
}
