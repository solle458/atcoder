package main

import (
	"fmt"
)

type Point struct {
	X, Y int
}

type PaD struct {
	p Point
	d int
}

type Queue struct {
	data []PaD
	size int
}

func NewQueue() *Queue {
	return &Queue{data: make([]PaD, 0), size: 0}
}

func (q *Queue) Push(p PaD) {
	q.data = append(q.data, p)
	q.size++
}

func (q *Queue) Pop() bool {
	if q.IsEmpty() {
		return false
	}
	q.size--
	q.data = q.data[1:]
	return true
}

func (q *Queue) Front() PaD {
	return q.data[0]
}

func (q *Queue) IsEmpty() bool {
	return q.size == 0
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func main() {
	var h, w int
	fmt.Scan(&h, &w)
	s := make([]string, h)
	for i := 0; i < h; i++ {
		fmt.Scan(&s[i])
	}
	start, end := Point{}, Point{}
	for i := 0; i < h; i++ {
		for j := 0; j < w; j++ {
			if s[i][j] == 'S' {
				start.Y = i
				start.X = j
			} else if s[i][j] == 'G' {
				end.Y = i
				end.X = j
			}
		}
	}
	var dy = [4]int{-1, 1, 0, 0}
	var dx = [4]int{0, 0, -1, 1}
	q1, q2 := NewQueue(), NewQueue()
	q1.Push(PaD{start, 0})
	q2.Push(PaD{start, 1})
	dist1, dist2 := make([][]int, h), make([][]int, h)
	for i := 0; i < h; i++ {
		dist1[i] = make([]int, w)
		dist2[i] = make([]int, w)
		for j := 0; j < w; j++ {
			dist1[i][j] = 1e9
			dist2[i][j] = 1e9
		}
	}
	dist1[start.Y][start.X] = 0
	dist2[start.Y][start.X] = 0
	for !q1.IsEmpty() {
		pad := q1.Front()
		p := pad.p
		d := pad.d
		q1.Pop()
		x, y := p.X, p.Y
		b, e := 0, 2
		if d == 0 {
			b = 2
			e = 4
		}
		for i := b; i < e; i++ {
			ny, nx := y+dy[i], x+dx[i]
			if ny < 0 || ny >= h || nx < 0 || nx >= w {
				continue
			}
			if s[ny][nx] == '#' {
				continue
			}
			if dist1[ny][nx] <= dist1[y][x]+1 {
				continue
			}
			dist1[ny][nx] = dist1[y][x] + 1
			q1.Push(PaD{Point{nx, ny}, (d + 1) % 2})
		}
	}
	for !q2.IsEmpty() {
		pad := q2.Front()
		p := pad.p
		d := pad.d
		q2.Pop()
		x, y := p.X, p.Y
		b, e := 0, 2
		if d == 0 {
			b = 2
			e = 4
		}
		for i := b; i < e; i++ {
			ny, nx := y+dy[i], x+dx[i]
			if ny < 0 || ny >= h || nx < 0 || nx >= w {
				continue
			}
			if s[ny][nx] == '#' {
				continue
			}
			if dist2[ny][nx] <= dist2[y][x]+1 {
				continue
			}
			dist2[ny][nx] = dist2[y][x] + 1
			q2.Push(PaD{Point{nx, ny}, (d + 1) % 2})
		}
	}
	ans := min(dist1[end.Y][end.X], dist2[end.Y][end.X])
	if ans == 1e9 {
		fmt.Println(-1)
	} else {
		fmt.Println(ans)
	}
}
