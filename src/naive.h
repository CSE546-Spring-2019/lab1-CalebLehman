#ifndef NAIVE_H
#define NAIVE_H

#include <stdio.h>

/***************************************************************************
* Given a valid file pointer, the length of the file, and a string,        *
* returns a count of the number of occurrences of the string in the file.  *
* Counts using a sliding window approach, checking each position in the    *
* file as a possible start to a copy of the search string                  *
***************************************************************************/
size_t countSlidingWindow(FILE* file, long int file_length, const char* string);

#endif // NAIVE_H
