//~0
//~1
//~2
//~3
//~4
//~5
//~6
//~7
//~8
//~9
//&Python: 1 minutes 8.5 seconds
//&C++: 11.1 seconds

package main

var array [50000]int
var size int = 50000

// Sorts the array in increasing order
func selection_sort() {
    var i int
    for i = 0; i < size; i++ {
        var min = array[i]
        var min_index = i
	var j int
        for j = i+1; j < size; j++ {
            if array[j] < min {
                min = array[j]
                min_index = j
            }
        }

        if min_index != i {
            // Swap i and min_index
            array[min_index] = array[i]
            array[i] = min
        }
    }
}

func main() {
    // Create the array to sort
    var i int
    for i = 0; i < size; i++ {
        array[i] = size-i-1
    }

    // Sort the array
    selection_sort()

    // Print the sorted array
    var j int
    for j = 0; j < 10; j++ {
        println(array[j])
    }
}
