//~Success

package main

func main() {
	var i int
	for i = 0; i < 4; i++ {
		if (i < 3) {
			continue
		} else {
			break
		}
		println(i)
	}
	println("Success")
}
