//~255
//~+1.200000e-001
//~+1.200000e-001
//~+1.200000e+001
//~true
//~false
//~76
//~10
//~hello
//~
//~hello\n

package main

func main() {
	println(255)
	//println(0377) according to the specification 1: You do not need to support octal or hexadecimal integer literals
	//println(0xff) I've implemented raw string instead

	println(0.12)
	println(.12)
	println(12.)

	println(true)
	println(false)

	println('L')
	println('\n')

	println("hello\n")
	println(`hello\n`)
}
