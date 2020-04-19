package test

type t bool
type z bool
type str string
type float float64
type float2 float


func test_func(a string, a2 string) int {
	return 5
}

func main() {
	//test_func("str", 5)
	type t z
	type z bool

	var test z = z(true)
	type test2 z
	type test3 test2
	var x test3 = test3(true)
	type str2 str
	type str3 str2
	type float3 float2
	var y str3 = str3("str")
	var fl float3 = float3(5.5)

	var zzzz = 'a' + 'a'
	
	if 5 + "str" {
	}

	if !test_func("s", "s") {
	}
	

	/*var test t = t(true)
	var a int = 5
	if a + test(5) {
	}*/

	/*var test t = t(true)
	var test2 t = t(true)	
	if !test {		
	}*/
}

//var test int = 5 + 5 + 5 * 2 / 10
