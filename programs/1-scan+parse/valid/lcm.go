package main 

func main (){
	println(lcm(10,25))
}

func lcm (a int, b int) int{
	lcm := 0
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
	return lcm;
}
