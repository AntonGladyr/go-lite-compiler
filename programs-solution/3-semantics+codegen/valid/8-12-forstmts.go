//~infinite
//~0
//~1
//~2
//~0
//~1
//~2
//~0
//~0
//~1
//~1
//~2
//~2
//~0
//~0
//~0
//~Success

package main

func main() {
	for {
		println("infinite")
		break
	}

	var x int = 0
	for x < 3 {
		println(x)
		x++
	}

	var i int
	for i = 0; i < 3; i++ {
		println(i)
	}

	var a, b int
	for a, b = 0, 0; a < 3; b, a = a, b {
		println(a)
		a++
	}

	for a = 0; a < 3; a++ {
		var a int
		println(a)
	}

	println("Success")
}
