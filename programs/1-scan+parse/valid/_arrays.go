package main

func main() {

    var a [5][5]int
    println("emp:", a)

    a[4] = 100
    println("set:", a)
    println("get:", a[4])

    println("len:", len(a))

    println("dcl:", b)

    var twoD [2][3]int
    for i := 0; i < 2; i++ {
        for j := 0; j < 3; j++ {
            twoD[i][j] = i + j
        }
    }
    println("2d: ", twoD)

    var x [3]int
    x[0] = 1
    x[1] = 2
    x[2] = 3
}
