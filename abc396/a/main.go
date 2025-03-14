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

	var n int
	fmt.Fscan(r, &n)
	a := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(r, &a[i])
	}
	for i := 0; i < n-2; i++ {
		if a[i] == a[i+1] && a[i+1] == a[i+2] {
			fmt.Fprintln(w, "Yes")
			return
		}
	}
	fmt.Fprintln(w, "No")
}
