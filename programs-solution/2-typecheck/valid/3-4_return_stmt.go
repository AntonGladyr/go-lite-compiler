package main

func incr(x float64) float64 {
	return x + 1.0
}




func main() {
	return
}

func ret_loop_3part() int {
	for ; ; {
		print(0)
	}
}

func ret_loop_inf() int {
	for {
		print(0)
	}
}

func ret_if() int {
	if true {
		return 0
	} else if false {
		return 1
	} else {
		return 2
	}
}

func ret_switch() int {
	switch {
		case true:
			return 0
		case false:
			return 1
		default:
			return 2
	}
}
