// this is to check if the integer is a plalindrome
package main

func main (){

    var number, r , i, sum int
    var count =0;
    fmt.Scan(&number);
    for i =number  ;i >0; i/10 {
            r = number%10;
            sum = (sum*10)+r;
    }
    if(number ==sum){
        print("It is a palindrome")

    }else{
        print("Not a palindrome")
    }

}