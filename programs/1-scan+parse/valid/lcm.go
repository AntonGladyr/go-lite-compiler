package main 

func main (){
	println(gcd(10,25))
}

func lcm (a int, b int) int{
	lcm := o
	if a >b{
		lcm =a
	}else{
		lcm = b; 
	}

	for true {
		if lcm%b ==0 && lcm%a ==0 {
			return lcm
		}
		lcm++;
	}

}