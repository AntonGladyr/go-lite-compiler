package main
var x int // type only
var y = 42 // expression only
var z int = 1 // type and expression

/* declare multiple identifiers at once */
var x1, x2 int
var y1, y2 = 42, 43
var z1, z2 int = 1, 2

/* a list of variable specifications */
var (
        x1, x2 int
        y1, y2 = 42, 43
        z1, z2 int = 1, 2
)
