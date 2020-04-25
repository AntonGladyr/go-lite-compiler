package main

func switch_stmts() {
	var x int

	// no expression
	switch {
		case x < 0:
		case x > 0:
		default:
	}

	// expression, no default
	switch x {
		case 0:
		case 1, 3, 5, 7, 9:
	}

	// empty
	switch {

	}
} 
