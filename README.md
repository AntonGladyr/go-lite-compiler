# GoLang Project

The goal of the project is to master modern techniques and tools for building a fully functional compiler. GoLite compiler is a complete compiler for a significant, non-trivial subset of Go language. From the list of Go features, GoLite  supports  only  Go  instructions  and  optionalsemi-colons. For more details, see the _Report.pdf_ .

# Building scripts
- run ./buildMakefile.sh to recreate the Makefile at the root whenever a new file is added
- call ./build.sh to build the compiler

## Resources

* Charles N. Fischer, Richard Joseph LeBlanc, Ronald Kaplan Cytron (2010). _Crafting a Compiler._ Pearson Education, Inc.: Addison-Wesley.
* <https://golang.org/ref/spec>
* <https://cmake.org/cmake/help/v2.8.8/cmake.html#module:FindBISON>
* <http://www.jonathanbeard.io/tutorials/FlexBisonC++>
* <http://westes.github.io/flex/manual/Start-Conditions.html>
* <https://gobyexample.com>
* <https://en.wikipedia.org/wiki/Quicksort>
* <https://www.geeksforgeeks.org/quick-sort/>
* <https://medium.com/@rgalus/sorting-algorithms-quick-sort-implementation-in-go-9ebfd91fe95f>

# Template

* `programs`: Test programs are organized by compilation phase and by expected result. Valid programs should output `OK` and status code `0`, while invalid programs should output `Error: <description>` and status code `1`.
  * `Scan+parse`: Runs both the scanner and parser phases
  * `Typecheck`: Runs until the end of the typechecker phase
  * `Codegen`: Runs until compiler outputs the target code
* `src`: Source code
* `build.sh`: Builds compiler using `Make`
* `run.sh`: Runs compiler using two arguments (mode - $1 and input file - $2)
* `test.sh`: Automatically runs compiler against test programs in the programs directory and checks the output
