# GoLang Project

* `Andy Jian`: 260741607
* `Victor Massenet`: 260779781
* `Anton Gladyr`: 260892882

# Building scripts
- run ./buildMakefile.sh to recreate the Makefile at the root whenever a new file is added
- call ./build.sh to build the compiler

## Resources

* Instructor Alex Krolik
* Charles N. Fischer, Richard Joseph LeBlanc, Ronald Kaplan Cytron (2010). _Crafting a Compiler._ Pearson Education, Inc.: Addison-Wesley.
* Lecture slides
* <https://cmake.org/cmake/help/v2.8.8/cmake.html#module:FindBISON>
* <http://www.jonathanbeard.io/tutorials/FlexBisonC++>
* <http://westes.github.io/flex/manual/Start-Conditions.html>
* <https://en.wikipedia.org/wiki/Quicksort>
* <https://www.geeksforgeeks.org/quick-sort/>
* <https://medium.com/@rgalus/sorting-algorithms-quick-sort-implementation-in-go-9ebfd91fe95f>

# Assignment Template

To organize your assignments and project for class, please follow the skeleton provided in this repository

We provide 3 scripts for convenience and two directories for organization:

* `programs`: Test programs are organized by compilation phase and by expected result. Valid programs should output `OK` and status code `0`, while invalid programs should output `Error: <description>` and status code `1`.
  * `Scan+parse`: Runs both the scanner and parser phases
  * `Typecheck`: Runs until the end of the typechecker phase
  * `Codegen`: Runs until your compiler outputs the target code
* `src`: Source code for your assignment
* `build.sh`: Builds your compiler using `Make` or similar. You should replace the commands here if necessary to build your compiler
* `run.sh`: Runs your compiler using two arguments (mode - $1 and input file - $2). You should replace the commands here if necessary to invoke your compiler
* `test.sh`: Automatically runs your compiler against test programs in the programs directory and checks the output

Comments found in both files provide more details as to the requirements. Since a large portion of grading is performed automatically, please ensure to follow the input/output specifications **exactly**. You must be able to run the provided scripts on the SOCS Trottier machines.
