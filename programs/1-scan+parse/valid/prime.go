// this is to check if the integer is a prime
package main

func main (){
    var number , i int
    number =11
    
    for i =2  ;i <number; i++ {
            if(number%i ==0 ){
				print("The number is not a prime number ")
				break
			}
            
    }
	print("The number is  a prime number ")
}
