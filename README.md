# CS134: Lab0
## Jesse Joseph

### Files
* lab0.h: Interface for lab0 module.
* lab0.c: Implementation file for lab0.
* Makefile: Compilation recipes
* img/
	* segfaultbacktrace.PNG: screen capture from GDB of backtrace resulting in forced segmentation fault
	* nullptr.PNG: screen capture from GDB of the pointer resulting in prior segmentation fault set to NULL

### Build
Simply run `make` to make the lab0 executable.
* `make check` makes a lab0 executable with a symbol table for GDB, then runs a series of functionality tests. I don't believe I did this the way that Professor Kampe was looking for, but I wasn't sure how else to do it.
	* First, creates a test file called "testfile". 
	* Next, runs basic functionality check copying "testfile" to "testcopy" and prints the contents of "testcopy", which should read `hello world`.
	* Performs additional tests for error behavior:
		* Force and catch a segmentation fault with the --segfault and --catch options
		* Force a segmentation fault with --segfault without catching
		* Force exit by omitting exit file
* `make clean` removes all testing files and the "lab0" executable.
* `make dist` builds the distribution tarball.

### Usage
`./lab0 --input=<inputfile> --output=<outputfile> [options]`
Copies the contents of `inputfile` to `outputfile`. `--input` and `--output` are required arguments.

_options_
* `-s`, `--segfault` forces a segmentation fault
* `-c`, `--catch` catches the segmentation fault, if one is forced.
