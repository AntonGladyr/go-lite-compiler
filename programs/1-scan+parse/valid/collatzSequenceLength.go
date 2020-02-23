package main

func main() {
  var value int = 100

  var sequence int = collatzSequenceLength(value)
	

  println("The sequence length is: ", sequence)
}

func collatz(x int) int {
  if (x % 2) == 0 {
    return x / 2
  } else {
    return (x * 3) + 1
  }
}

func collatzSequenceLength(x int) int {
  var seqLength int = 1

  for x != 1 {
    x = collatz(x)
    seqLength ++
  }

  return seqLength
}
