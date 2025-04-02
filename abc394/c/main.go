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
	runes := []rune(s)
	for i := len(runes) - 1; i >= 1; i-- {
		if runes[i] == 'A' && runes[i-1] == 'W' {
			runes[i] = 'C'
			runes[i-1] = 'A'
		}
	}
	fmt.Fprintln(w, string(runes))
}
