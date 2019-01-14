/**
 * Author: Caleb Lehman (lehman.346@osu.edu)
 */

#ifndef NAIVE_H
#define NAIVE_H

#include <stdio.h>

#include "defs.h"

/**
 * Given a valid file pointer and a string,
 * returns the appropriate counts, namely
 *   the count of bytes in the file,
 *   the count of occurrences of the string in the file
 * Counts occurrences using a sliding window approach, checking each
 * position in the file as a possible start to a copy of the search string.
 */
Counts countNaive(FILE* file, const char* string);

#endif // NAIVE_H
