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

	x, ans, fac := 0, 0, 1
	fmt.Fscan(r, &x)
	for fac != x {
		ans++
		fac *= ans
	}
	fmt.Fprintln(w, ans)
}
