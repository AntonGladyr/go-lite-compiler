package main

func main() {

    s := make([]string, 3)
    println("emp:", s)

    s[0] = "a"
    s[1] = "b"
    s[2] = "c"
    println("set:", s)
    println("get:", s[2])

    println("len:", len(s))

    s = append(s, "d")
    s = append(s, "e", "f")
    println("apd:", s)

    c := make([]string, len(s))
    copy(c, s)
    println("cpy:", c)

    l := s[2:5]
    println("sl1:", l)

    l = s[:5]
    println("sl2:", l)

    l = s[2:]
    println("sl3:", l)

    t := []string{"g", "h", "i"}
    println("dcl:", t)

    twoD := make([][]int, 3)
    for i := 0; i < 3; i++ {
        innerLen := i + 1
        twoD[i] = make([]int, innerLen)
        for j := 0; j < innerLen; j++ {
            twoD[i][j] = i + j
        }
    }
    println("2d: ", twoD)
}
