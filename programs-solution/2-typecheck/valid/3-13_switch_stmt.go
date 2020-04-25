package main

func main() {
	var x = 0
	switch x {
		case 1:
			x++
		case 2,3:
			x++
		default:
			x++
	}

	switch x {
		case 1:
			var x int
		case 2,3:
			var x int
		default:
			var x int
	}

	switch {
		case true:
		case false:
	}

	type num int
	var r num = num(0)
	switch r {
		case num(1):
		case num(2),num(3):
	}
}
