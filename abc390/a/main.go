package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	w := bufio.NewWriter(os.Stdout)
	defer w.Flush()

	l, ans := make([]int, 5), make([]int, 5)
	for i := 0; i < 5; i++ {
		fmt.Fscan(r, &l[i])
		ans[i] = i + 1
	}
	ng := 0
	for i := 0; i < 4; i++ {
		if l[i]-1 != i {
			ng++
			swap(&l[i], &l[i+1])
		}
	}
	if ng == 1 {
		for i := 0; i < 5; i++ {
			if l[i] != ans[i] {
				fmt.Fprintln(w, "No")
				return
			}
		}
	} else {
		fmt.Fprintln(w, "No")
		return
	}
	fmt.Fprintln(w, "Yes")
}

func swap(a, b *int) {
	*a, *b = *b, *a
}
