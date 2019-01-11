# CSE 5462 - Lab 1

## Description

A program to 

1. Count the number of bytes in a file
2. Count the number of occurrences or a specified string in the file

and to print the results to console and to an output file.

Implementations of string matching written both "naively" (check every position
for a match) and using Knuth-Morris-Pratt (KMP) algorithm. Written in C.

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

Once build, the program can be tested by running `./run_tests.sh`. This runs a
series of tests located in the `tests` directory and prints the results
(Passed/Failed).
