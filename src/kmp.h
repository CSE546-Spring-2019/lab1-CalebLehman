#ifndef KMP_H
#define KMP_H

#include <stdio.h>

#include "defs.h"

/***************************************************************************
* Given a valid file pointer and a string,                                 *
* returns the appropriate counts, namely                                   *
*   the count of bytes in the file,                                        *
*   the count of occurrences of the string in the file                     *
* Counts occurrences using an implementation of the Knuth-Morris-Pratt     *
* as described in Introduction to Algorithms by CLRS                       *
***************************************************************************/
Counts countKnuthMorrisPratt(FILE* file, const char* string);
/***************************************************************************
* Given a string and table of the same length.                             *
* fills the table so that table[i] is the longest proper prefix of         *
* string[0..i] which is also a suffix of string[0..i].                     *
***************************************************************************/
void fillLPSTable(const char* string, size_t table[], size_t length);

#endif // KMP_H
