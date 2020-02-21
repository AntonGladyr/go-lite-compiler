//wrong delcaration of a struct 
package main 


type point struct {
	x, y, z int
}


func main(){
	var p point = point{ 1, 2, 3 }
}