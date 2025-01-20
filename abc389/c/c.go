package main

import (
	"bufio"
	"fmt"
	"os"

	"github.com/liyue201/gostl/ds/deque"
)

func main() {
	r := bufio.NewReader(os.Stdin)
	w := bufio.NewWriter(os.Stdout)
	defer w.Flush()

	var Q int
	fmt.Fscan(r, &Q)
	dq := deque.New[int]()
	p := 0
	dq.PushBack(p)
	for i := 0; i < Q; i++ {
		var q, l, k int
		fmt.Fscan(r, &q)
		if q == 1 {
			fmt.Fscan(r, &l)
			if dq.Empty() {
				dq.PushBack(l)
			} else {
				dq.PushBack(l + dq.Back())
			}
		} else if q == 2 {
			dq.PopFront()
			if !dq.Empty() {
				p = dq.Front()
			}
		} else {
			fmt.Fscan(r, &k)
			fmt.Fprintln(w, dq.At(k-1)-p)
		}
	}
}
