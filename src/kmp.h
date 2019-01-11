#ifndef KMP_H
#define KMP_H

#include <stdio.h>

/***************************************************************************
* Given a valid file pointer, the length of the file, and a string,        *
* returns a count of the number of occurrences of the string in the file.  *
* Counts using an implementation of the Knuth-Morris-Pratt algorithm       *
* described in Introduction to Algorithms by CLRS                          *
***************************************************************************/
size_t countKnuthMorrisPratt(FILE* file, long int file_length, const char* string);
/***************************************************************************
* Given a string and table of the same length.                             *
* fills the table so that table[i] is the longest proper prefix of         *
* string[0..i] which is also a suffix of string[0..i].                     *
***************************************************************************/
void fillLPSTable(const char* string, size_t table[], size_t length);

#endif // KMP_H
