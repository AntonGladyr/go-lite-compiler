// this is to check if the integer is a prime
package main

func main (){

    var number, r , i, sum int
    var count =0;
    fmt.Scan(&number);
    for i =2  ;i <number; i++ {
            if(number%i ==0 ){
				fmt.Print("The number is not a prime number ")
				break
			}
            
    }
	fmt.Print("The number is  a prime number ")
}