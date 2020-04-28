//~1
//~2
//~4
//~5
//~5
//~5

package main

func main() {
	var a,b int = 1, 2
	println(a)
	println(b)

	a, a, b = 3, 4, 5
	println(a)
	println(b)

	a, b = b, a + 1
	println(a)
	println(b)
}
