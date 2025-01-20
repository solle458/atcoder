package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	var r = bufio.NewReader(os.Stdin)
	var w = bufio.NewWriter(os.Stdout)
	defer w.Flush()

	var s string
	fmt.Fscan(r, &s)
	fmt.Fprintln(w, int(s[0]-'0')*int(s[2]-'0'))
}
