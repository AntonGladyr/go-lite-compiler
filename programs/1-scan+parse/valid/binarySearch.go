package main
 
func binarySearch(count int, a []int) bool {
	h := len(a) - 1
    l := 0
    
 
    for l <= h {
        middle := (l + h) / 2
 
        if a[middle] < count {
            l = middle + 1
        }else{
            high = middle - 1
        }
    }
 
    if l == len(a) || a[l] != count {
        return false
    }
 
    return true
}
 
 
func main(){
    items := []int{2,6,10,56,63,66,99,100,101}
    if binarySearch(63, items)) {
		println("Found!")
	}else {
		println("Not Found ... ")
	}
}