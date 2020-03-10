package main

func dec_stmts() {
	// simple variable declarations
	var a1 int
	var a2 float64 = 0.0
	var a3 = 0.0

	// multiple variable declarations
	var a4, a5 string
	var a6, a7 string = "a", `b`
	var a8, a9 = 'a', 0

	// type alias
	type t1 int

	// arrays
	type t11 [4]int			// base type
	type t12 [4]t1			// type id
	type t14 [3][3]float64	// matrix
} 
