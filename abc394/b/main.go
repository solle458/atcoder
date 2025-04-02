package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

type Pair struct {
	first  any
	second any
}

func main() {
	r := bufio.NewReader(os.Stdin)
	w := bufio.NewWriter(os.Stdout)
	defer w.Flush()
	var n int
	fmt.Fscan(r, &n)
	s := make([]Pair, n)
	for i := 0; i < n; i++ {
		var str string
		fmt.Fscan(r, &str)
		s[i].first = len(str)
		s[i].second = str
	}
	sort.Slice(s, func(i, j int) bool {
		return s[i].first.(int) < s[j].first.(int)
	})
	for _, v := range s {
		fmt.Fprintf(w, "%s", v.second)
	}
	fmt.Fprintln(w)
}
