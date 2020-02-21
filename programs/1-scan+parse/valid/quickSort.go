package main 

<<<<<<< HEAD
func main (){
	print(quicksort([40,23,12,6,59,34]))
=======
func main() {
	slice := generateSlice(20)
	fmt.Println
>>>>>>> 526ae45f9ca2edb4e14c93ce13f9f5a35c696cb5
}
func quicksort(t[] int){
	if len(t) < 2 {
        return a
    }
      
    left, right := 0, len(t)-1
      
    pivot :=  52 %len(t);
      
    t[pivot], t[right] = t[right], t[pivot]
      
    for i:= 0; i<len(t);i++ {
        if t[i] < t[right] {
            t[left], t[i] = t[i], t[left]
            left++
        }
    }
      
    t[left], t[right] = t[right], t[left]
	  
	var x[] int 
	var y[] int 
	for i:=0 ; i<=left; i++{
		append (x,t[i]);
	}
	for i:=left+1 ; i<len(t); i++{
		append (x,t[i]);
	}
	append(t, quicksort(x))
	append(t, quicksort(y))
    
      
    return t
}