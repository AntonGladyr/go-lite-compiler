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
//&Python: 54.6 seconds
//&C++: 7.4 seconds

package main

var size = 25000
var arr [25000]int

func insertionSort() {
	var j int
	for j = 0; j < size; j++ {
		var key = arr[j]
		var i = j - 1
		for i >= 0 && arr[i] > key {
			arr[i+1] = arr[i]
			i = i - 1
		}

		arr[i+1] = key
	}
}

func main() {
	var j int
	for j = size - 1; j >= 0; j-- {
		arr[size - j - 1] = j
	}
	insertionSort()
	var i int
	for i = 0; i < 10; i++ {
		println(arr[i])
	}

}
