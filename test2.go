package test

type t bool
type z bool

func main() {
	type t z
	type z int

	var test t = t(true)
	//var a test = test(5)
	//if a + test(5) {
	//}

	/*var test t = t(true)
	var test2 t = t(true)	
	if !test {		
	}*/
}
//var test int = 5 + 5 + 5 * 2 / 10
