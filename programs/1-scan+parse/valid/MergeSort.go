package main

var array[10] int

func main() {

    var i int
    var arr[10] int
    array[0] = 5
    array[1] = 10
    array[2] = 12
    array[3] = 123
    array[4] = 40
    array[5] = 51
    array[6] = 78
    array[7] = 19
    array[8] = 5
    array[9] = 76


    arr = sort(0, 9)

    print("[")
    for i = 0; i < 10; i++{
	
        print(arr[i])
	if i != 9 {
        print(",")
	}
    }
     print("]")
}

func merge(l, m, h int) {

    var arr[10] int
    var i, j, k int

    for i = l;
    i <= m;
    i++{
        arr[i] = array[i]
    }

    for j = m + 1; j <= h; j++{
        arr[h + m + 1 - j] = array[j]
    }

    i = l
    j = h


    for k = l; k <= h; k++{
        if (arr[i] <= arr[j]) {
            array[k] = arr[i]
            i++
        } else {
            array[k] = arr[j]
            j--
        }

    }
}

func sort(l, h int)[10] int {

    if (l < h) {
        var m int
        m = (l + h) / 2

        sort(l, m)
        sort(m + 1, h)
        merge(l, m, h)
    }
    return array;

}
