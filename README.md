# CSE 5462 - Lab 1

## Description

A program to 

1. Count the number of bytes in a file
2. Count the number of occurrences or a specified string in the file

and to print the results to console and to an output file.

Implementations of string matching written both "naively" (check every position
for a match) and using Knuth-Morris-Pratt (KMP) algorithm.

## Building

### Normal Build (Implemented with KMP)

To build, run `make`. Resulting executable is `count` located in the `build` directory.

### Naive Build

To build, run `make naive`. Resulting executable is `count` located in the `build` directory.

## Running

To run, use command `./build/count <in-file> <search-string> <out-file>`, where
`<in-file>` is the input file to be counted/searched, `<search-string>` is the
string to search for, and `<out-file>` is the file to which results should be
printed.

## Testing

Once built, the program can be tested by running `./run_tests.sh`. This runs a
series of tests located in the `tests` directory and prints the results
(Passed/Failed).

### Adding New Tests

Tests are subdirectories of `tests` with names of the form `test*`. Inside each
individual test directory are two files, named `out` and `test.sh`.

`test.sh` should be a shell script containing a single command to run the
`count` program. The first argument to the script will be the build directory
containing `count`, the second argument will be the test directory, and the
third will be the path to the output file.

`out` should be the corresponding expected output file.

See the existing tests for examples.
