package main 

func main (){
	println(gcd(10,25))
}

func gcd (a int, b int) int{
	gcd := 1
	for i:=1 ; i< a && i< b ; i++ {
		if a&i ==0 && b%i ==0 {
			gcd =i;
		}
	}
	return gcd

}