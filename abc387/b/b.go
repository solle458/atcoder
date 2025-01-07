package main

import "fmt"

func main() {
	var x, ans int
	fmt.Scan(&x)
	for i := 1; i < 10; i++ {
		for j := 1; j < 10; j++ {
			if i*j != x {
				ans += i * j
			}
		}
	}
	fmt.Println(ans)
}
