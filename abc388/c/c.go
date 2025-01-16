package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"sort"
	"strconv"
)

var sc = bufio.NewScanner(os.Stdin)

func scanInt() (i int) {
	var err error
	sc.Scan()
	i, err = strconv.Atoi(sc.Text())
	if err != nil {
		log.Fatal(err)
	}
	return
}

func main() {
	sc.Split(bufio.ScanWords)

	n := scanInt()
	a := make([]int, n)
	for i := 0; i < n; i++ {
		a[i] = scanInt()
	}
	ans := 0
	for i := 0; i < n; i++ {
		key := a[i] * 2
		lb := sort.Search(len(a), func(j int) bool { return a[j] >= key })
		ans += n - lb
	}
	fmt.Println(ans)
}
