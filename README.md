# Code for SNS Assignment

## How to Run?
Use the makefile to compiler the projects, note the compiler on my machine is clang, if you are using gcc change the CC variable in the makefile to gcc. SImply make assignment\<number\> where number is between 1 and 10 both included

Example:

    make assignment1

The generated executable is stored in a build directory in the project folder. To run the generated executable use:

    ./build/assg1

NOTE: all the programs take input as arguments from the command line, crashes can and will occur if they aren't given properly. If you simply run the executables they will display an error message telling the user about how the programs are intended to be used, you can refer to that for seeing the CLI arguments and in which order they must be given in.  
