package utils

func max[T int | float64 | string](a, b T) T {
	if a > b {
		return a
	} else {
		return b
	}
}

func min[T int | float64 | string](a, b T) T {
	if a > b {
		return b
	} else {
		return a
	}
}

func Max[T int | float64 | string](a *T, b T) bool {
	if *a < b {
		*a = b
		return true
	} else {
		return false
	}
}

func Min[T int | float64 | string](a *T, b T) bool {
	if *a > b {
		*a = b
		return true
	} else {
		return false
	}
}

func Swap[T int | float64 | string](a, b *T) {
	*a, *b = *b, *a
}
