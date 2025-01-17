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
	
	var n int

	fmt.Fscan(r, &n)
	a := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(r, &a[i])
	}

	op := func(x, y int) int { return x + y }
	e := func() int { return 0 }
	mapping := func(f, x int) int { return f + x }
	composition := func(f, g int) int { return f + g }
	id := func() int { return 0 }

	seg := NewLazySegtree(a, op, e, mapping, composition, id)

	for i := 0; i < n; i++ {
		v := seg.Get(i)
		if v < n-i-1 {
			seg.Apply(i+1, i+1+v, 1)
			seg.Set(i, 0)
		} else {
			seg.Apply(i+1, n, 1)
			seg.Set(i, v-(n-i-1))
		}
	}

	for i := 0; i < n-1; i++ {
		fmt.Fprintf(w, "%d ", seg.Get(i))
	}
	fmt.Fprintln(w, seg.Get(n - 1))
}

type LazySegtree[S any, F any] struct {
	n, size, log int
	data         []S
	lazy         []F
	lazyFlag     []bool
	op           func(S, S) S // 区間マージ
	e            func() S     // 単位元
	mapping      func(F, S) S // 遅延適用
	composition  func(F, F) F // 遅延マージ
	id           func() F     // 遅延単位元
}

func NewLazySegtree[S any, F any](
	v []S,
	op func(S, S) S,
	e func() S,
	mapping func(F, S) S,
	composition func(F, F) F,
	id func() F,
) *LazySegtree[S, F] {
	n := len(v)
	log := 0
	for (1 << log) < n {
		log++
	}
	size := 1 << log
	data := make([]S, 2*size)
	lazy := make([]F, size)
	lazyFlag := make([]bool, size)

	for i := range data {
		data[i] = e()
	}
	for i := range lazy {
		lazy[i] = id()
	}

	for i := 0; i < n; i++ {
		data[size+i] = v[i]
	}
	for i := size - 1; i > 0; i-- {
		data[i] = op(data[2*i], data[2*i+1])
	}

	return &LazySegtree[S, F]{
		n:           n,
		size:        size,
		log:         log,
		data:        data,
		lazy:        lazy,
		lazyFlag:    lazyFlag,
		op:          op,
		e:           e,
		mapping:     mapping,
		composition: composition,
		id:          id,
	}
}

func (st *LazySegtree[S, F]) update(k int) {
	st.data[k] = st.op(st.data[2*k], st.data[2*k+1])
}

func (st *LazySegtree[S, F]) allApply(k int, f F) {
	st.data[k] = st.mapping(f, st.data[k])
	if k < st.size {
		st.lazy[k] = st.composition(f, st.lazy[k])
		st.lazyFlag[k] = true
	}
}

func (st *LazySegtree[S, F]) push(k int) {
	if st.lazyFlag[k] {
		st.allApply(2*k, st.lazy[k])
		st.allApply(2*k+1, st.lazy[k])
		st.lazy[k] = st.id()
		st.lazyFlag[k] = false
	}
}

func (st *LazySegtree[S, F]) Set(p int, x S) {
	p += st.size
	for i := st.log; i > 0; i-- {
		st.push(p >> i)
	}
	st.data[p] = x
	for i := 1; i <= st.log; i++ {
		st.update(p >> i)
	}
}

func (st *LazySegtree[S, F]) Get(p int) S {
	p += st.size
	for i := st.log; i > 0; i-- {
		st.push(p >> i)
	}
	return st.data[p]
}

func (st *LazySegtree[S, F]) Prod(l, r int) S {
	if l == r {
		return st.e()
	}

	l += st.size
	r += st.size

	for i := st.log; i > 0; i-- {
		if ((l >> i) << i) != l {
			st.push(l >> i)
		}
		if ((r >> i) << i) != r {
			st.push((r - 1) >> i)
		}
	}

	sml, smr := st.e(), st.e()
	for l < r {
		if l&1 == 1 {
			sml = st.op(sml, st.data[l])
			l++
		}
		if r&1 == 1 {
			r--
			smr = st.op(st.data[r], smr)
		}
		l >>= 1
		r >>= 1
	}

	return st.op(sml, smr)
}

func (st *LazySegtree[S, F]) Apply(l, r int, f F) {
	if l == r {
		return
	}

	l += st.size
	r += st.size

	for i := st.log; i > 0; i-- {
		if ((l >> i) << i) != l {
			st.push(l >> i)
		}
		if ((r >> i) << i) != r {
			st.push((r - 1) >> i)
		}
	}

	{
		l2, r2 := l, r
		for l < r {
			if l&1 == 1 {
				st.allApply(l, f)
				l++
			}
			if r&1 == 1 {
				r--
				st.allApply(r, f)
			}
			l >>= 1
			r >>= 1
		}
		l = l2
		r = r2
	}

	for i := 1; i <= st.log; i++ {
		if ((l >> i) << i) != l {
			st.update(l >> i)
		}
		if ((r >> i) << i) != r {
			st.update((r - 1) >> i)
		}
	}
}
