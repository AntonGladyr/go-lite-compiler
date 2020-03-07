package main

type num int         // simple type definition

type point struct {  // point is a struct
	x, y float64
}

type (
	num int
        point struct {
        	x, y float64
	}
)

type Car struct {
	Name, Model, Color string
	WeightInKg         float64
}

func main() {
	/*c := Car{
		Name:       "Ferrari",
		Model:      "GTC4",
		Color:      "Red",
		WeightInKg: 1920,
	}*/

	// Accessing struct fields using the dot operator
	println("Car Name: ", c.Name)
	println("Car Color: ", c.Color)

	// Assigning a new value to a struct field
	c.Color = "Black"
	println("Car: ", c)
}
