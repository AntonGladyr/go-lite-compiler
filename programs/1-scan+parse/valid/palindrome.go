// this is to check if the integer is a plalindrome
package main
import "fmt"

funct main (){

    var number, r , i, sum int
    var count =0;
    fmt.Scan(&number);
    for i =number  ;i >0; i/10 {
            r = number%10;
            sum = (sum*10)+r;
    }
    if(number ==sum){
        fmt.Print("It is a palindrome")

    }else{
        fmt.Print("Not a palindrome")
    }

}