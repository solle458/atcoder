package utils

func Max[T int | float64 | string](a, b *T) bool {
	if *a < *b {
		*a = *b
		return true
	} else {
		return false
	}
}

func Min[T int | float64 | string](a, b *T) bool {
	if *a > *b {
		*a = *b
		return true
	} else {
		return false
	}
}
