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

	var s string
	fmt.Fscan(r, &s)
	for _, c := range s {
		if c == '2' {
			fmt.Fprint(w, "2")
		}
	}
	fmt.Fprintln(w)
}
