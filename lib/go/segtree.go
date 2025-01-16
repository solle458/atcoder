package main

import (
	"fmt"
	"math"
)

type Operation[T any] struct {
	IdentifyElement T            // 単位元
	Operation       func(T, T) T // 区間マージ
	Mapping         func(T, T) T // 遅延値の適応
	Composition     func(T, T) T // 遅延値のマージ
}

type LazySegtree[T any] struct {
	n          int
	data, lazy []T
	op         Operation[T]
	lazyOn     []bool
}

func NewLazySegtree[T any](size int, op Operation[T]) *LazySegtree[T] {
	n := 1
	for n < size {
		n *= 2
	}
	data := make([]T, 2*n-1)
	lazy := make([]T, 2*n-1)
	lazyOn := make([]bool, 2*n-1)

	// 単位元で初期化
	for i := range data {
		data[i] = op.IdentifyElement
		lazy[i] = op.IdentifyElement
	}

	return &LazySegtree[T]{
		n:      n,
		data:   data,
		lazy:   lazy,
		op:     op,
		lazyOn: lazyOn,
	}
}

func (st *LazySegtree[T]) Set(i int, x T) {
	i += st.n - 1
	st.data[i] = x
	for i > 0 {
		i = (i - 1) / 2
		st.data[i] = st.op.Operation(st.data[i*2+1], st.data[i*2+2])
	}
}

func (st *LazySegtree[T]) Get(i int) T {
	st.propagate(i+st.n-1, 0, 1) // 遅延値を適用してから取得
	return st.data[i+st.n-1]
}

func (st *LazySegtree[T]) propagate(i, l, r int) {
	if !st.lazyOn[i] {
		return
	}
	// 遅延値を適用
	st.data[i] = st.op.Mapping(st.data[i], st.lazy[i])
	if r-l > 1 {
		// 子ノードへの伝搬
		st.lazyOn[i*2+1] = true
		st.lazyOn[i*2+2] = true
		st.lazy[i*2+1] = st.op.Composition(st.lazy[i*2+1], st.lazy[i])
		st.lazy[i*2+2] = st.op.Composition(st.lazy[i*2+2], st.lazy[i])
	}
	st.lazyOn[i] = false
}

func (st *LazySegtree[T]) update(a, b int, x T, k, l, r int) {
	st.propagate(k, l, r)
	if a >= r || b <= l {
		return
	}
	if a <= l && r <= b {
		st.lazy[k] = st.op.Composition(st.lazy[k], x)
		st.lazyOn[k] = true
		st.propagate(k, l, r)
		return
	}
	mid := (l + r) / 2
	st.update(a, b, x, 2*k+1, l, mid)
	st.update(a, b, x, 2*k+2, mid, r)
	st.data[k] = st.op.Operation(st.data[2*k+1], st.data[2*k+2])
}

func (st *LazySegtree[T]) Update(a, b int, x T) {
	st.update(a, b, x, 0, 0, st.n)
}

func (st *LazySegtree[T]) query(a, b, k, l, r int) T {
	st.propagate(k, l, r)
	if b <= l || r <= a {
		return st.op.IdentifyElement
	}
	if a <= l && r <= b {
		return st.data[k]
	}
	mid := (l + r) / 2
	lv := st.query(a, b, 2*k+1, l, mid)
	rv := st.query(a, b, 2*k+2, mid, r)
	return st.op.Operation(lv, rv)
}

func (st *LazySegtree[T]) Query(a, b int) T {
	return st.query(a, b, 0, 0, st.n)
}

func main() {
	op := Operation[int]{
		IdentifyElement: math.MaxInt32,                           // 初期値は ∞
		Operation:       func(a, b int) int { return min(a, b) }, // 最小値
		Mapping:         func(a, x int) int { return a + x },     // 加算
		Composition:     func(a, b int) int { return a + b },     // 遅延値の加算
	}

	// セグメントツリーの作成
	n := 8
	st := NewLazySegtree[int](n, op)

	// 初期値を設定
	for i := 0; i < n; i++ {
		st.Set(i, i)
	}

	// 現在の配列を出力
	fmt.Println("Initial array:")
	for i := 0; i < n; i++ {
		fmt.Println(st.Get(i))
	}

	// 区間加算 [2, 5) に 10 を加算
	st.Update(2, 5, 10)

	// 配列を出力
	fmt.Println("After Update [2, 5) +10:")
	for i := 0; i < n; i++ {
		fmt.Println(st.Get(i))
	}

	// 区間最小値を取得 [0, 8)
	fmt.Println("Query [0, 8):", st.Query(0, 8)) // 出力: 0

	// 区間最小値を取得 [2, 5)
	fmt.Println("Query [2, 5):", st.Query(2, 5)) // 出力: 12
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
