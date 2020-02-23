package main 

func main (){
	print(power(3,10));
}

func power(a int, b int ) int {
	var count =1;
	for i:=0 ; i<b ; i++{
		count = count*a
	}

	return count
}
