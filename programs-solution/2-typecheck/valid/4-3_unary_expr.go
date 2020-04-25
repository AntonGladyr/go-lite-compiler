package main

func base_types() {
	 var        a int
	  var       b float64
	  var       c rune
	  var       d string
	  var       e bool

	// Unary plus
	println(+a)
	println(+b)
	println(+c)

	// Unary negation
	println(-a)
	println(-b)
	println(-c)

	// Unary bit-not
	println(^a)
	println(^c)

	// Unary logical not
	println(!e)
}

func type_aliases() {
	 type        t1 int
	      type   t2 float64
	    type     t3 rune
	       type  t4 string
	       type  t5 bool
	var a t1
	var b t2
	 var        c t3
	 var        d t4
	 var        e t5

	// Unary plus
	println(+a)
	println(+b)
	println(+c)

	// Unary negation
	println(-a)
	println(-b)
	println(-c)

	// Unary bit-not
	println(^a)
	println(^c)

	// Unary logical not
	println(!e)
}
