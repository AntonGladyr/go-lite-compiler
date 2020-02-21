package main 

func main (){
	println(coinChange(0,[1,2,5,10], 14))
}
func coinChange( index int, t[] int , n int ) int {
	if n == 0 {
		return 0;
	}

	var maxVal = n/t[index]
	var minVal int =  2147483647 // maximum value of an integer
	for i : =0; i< maxVal ; i++{
		if amount >= i*t[index]{
			rest := coinChange(index+1, t, n - i*t[index])
			if rest != -1 {
				minVal = minimum(minVal, rest+i)
			}
		}
	}
	if minVal == 2147483647 {
		return -1
	}else{
		return minVal
	}
}

func minimum (a int, b int )int {
	if (a>b){
	return b;
	}
	else {
	return a 
	}
}