package main

func main() {

    i := 2
    print("Write ", i, " as ")
    switch i {
    case 1:
        println("one")
    case 2:
        println("two")
    case 3:
        println("three")
    }

    switch time.Now().Weekday() {
    case time.Saturday, time.Sunday:
       println("It's the weekend")
    default:
        println("It's a weekday")
    }

    t := time.Now()
    switch {
    case t.Hour() < 12:
        println("It's before noon")
    default:
        println("It's after noon")
    }

    whatAmI := func(i interface{}) {
        switch t := i.(type) {
        case bool:
            println("I'm a bool")
        case int:
            println("I'm an int")
        default:
            printf("Don't know type %T\n", t)
        }
    }
    whatAmI(true)
    whatAmI(1)
    whatAmI("hey")
}
