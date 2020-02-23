// this is to check if the number is a plalindrome
package main

func main (){
    var t, number int
    var r, sum int
    
    r, sum = 0, 0

    number = 101

    t = number

    for number > 0 {
        r = number % 10 
        sum = (sum * 10) + r
        number = number / 10
    }

    if t == sum {
        println("It is a palidrome")
    } else {
        println("NOT a palidrome")
    }
}
