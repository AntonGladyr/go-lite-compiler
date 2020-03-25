package main

// simple variable declarations

var test string = `s\bt"rtest	test
i\ng\n`

var x int
var y int
var b bool
var c bool
var y int = -x
var y int = +x
var c int = !b
var y int = ^x
var y int = - -x
var y int = + +x
var c int = !!c
var y int = ^^x

var x int
var y int
var r int
var b bool
var c bool
var r int = (1)
var r int = (5 + 1)*2
var r int = x + 1
var r int = x - 1
var r int = x * 1
var r int = x / 1
var r int = x % 1
var r int = x & 1
var r int = x | 1
var r int = x ^ 1
var r int = x &^ 1
var r int = x << 1
var r int = x >> 1
var c int = b && b
var c int = b || b
var c int = x < y
var c int = x <= y
var c int = x == y
var c int = x != y
var c int = x >= y
var c int = x > y
var r int = x + y

var a, b, c int


// single dimension array declaration
var x [3]int
var m, n int

// array access lhs
var x[0] int = 1
var x[1] float64= 2
var x[2] string = 3

// array access rhs
var y1, y2, y3, y4, y5 int
var y1 int= x[0]
var y2 string = x[1]
var y3 bool = x[2]
var y4 string = x[m]
var y5 rune = x[m + 1]

// multi-dimensional array
var a [1][2]float64
/*a[0][0] = 0.0
a[0][1] = 0.0
a[m][n] = 0.0


// multi-dimensional array access rhs
var b1, b2, b3 float64
b1 = a[0][0]
b2 = a[0][1]
b3 = a[m][n]
*/
