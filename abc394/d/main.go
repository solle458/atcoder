package main

import (
	"bufio"
	"fmt"
	"os"

	"github.com/liyue201/gostl/ds/stack"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	w := bufio.NewWriter(os.Stdout)
	defer w.Flush()
	var s string
	fmt.Fscan(r, &s)
	mp := make(map[string]string)
	mp[")"] = "("
	mp["}"] = "{"
	mp["]"] = "["
	mp[">"] = "<"
	st := stack.New[byte]()
	for i := 0; i < len(s); i++ {
		if mp[string(s[i])] != "" && !st.Empty() && st.Top() == byte(mp[string(s[i])][0]) {
			st.Pop()
		} else {
			st.Push(s[i])
		}
	}
	if st.Empty() {
		fmt.Fprintln(w, "Yes")
	} else {
		fmt.Fprintln(w, "No")
	}
}
