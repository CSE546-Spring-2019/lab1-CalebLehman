/**
 * Author: Caleb Lehman (lehman.346@osu.edu)
 */

#ifndef DEFS_H
#define DEFS_H

extern const size_t MAX_CHUNK;          // The size of largest chunk that should be read from file
extern const size_t MAX_SEARCH_STR_LEN; // The maximum allowed size for a search string

typedef struct Counts {
    long long unsigned count_bytes;     // Stores the number of bytes in file
    long long unsigned count_matches;   // Stores the number of matches (to a string) in file
} Counts;

#endif // DEFS_H
