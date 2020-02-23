// this is to check if the integer is a palindrome
package main

func main (){
	number:=11
    var r ,temp, sum int
 
    for{
        r = number%10
        sum = sum*10 + r
        number /= 10
 
        if(number==0){
            break 
        }
    }
    if(temp == sum){
        print("It is a palindrome")

    }else{
        print("Not a palindrome")
    }

}
