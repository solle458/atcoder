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
	if 400%n == 0 {
		fmt.Fprintln(w, 400/n)
	} else {
		fmt.Fprintln(w, -1)
	}
}
