#include <string.h>
#include <stdlib.h>

#include "defs.h"
#include "kmp.h"

size_t countKnuthMorrisPratt(FILE* file, long int file_length, const char* string) {
    size_t str_length = strlen(string);

    // Generate longest-prefix-suffix table
    size_t* table = malloc(str_length * sizeof(*table));
    fillLPSTable(string, table, str_length);

    size_t count = 0;

    char buffer[MAX_CHUNK]; // A buffer to store bytes read from file
    size_t bytes_read = 0;  // Total number of bytes read from file
    size_t str_pos = 0;     // Current position in search string
                            //   (previous positions have been matched)

    // Loop over file, reading into buffer
    while (bytes_read < file_length) {
        size_t new_bytes = fread(buffer, sizeof(char), MAX_CHUNK, file);

        size_t offset = 0;  // Offset within buffer

        // Loop over buffer, checking for matches
        while (offset < new_bytes) {
            // Match as far as possible
            //   starting at str_pos in search string and
            //   starting at offset in buffer
            while ((str_pos < str_length) && (offset < new_bytes) && (string[str_pos] == buffer[offset])) {
                offset++;
                str_pos++;
            }

            // At this point, either
            //   have matched a copy of search string,
            //   have reached a mismatch, or
            //   have reached end of buffer
            if (str_pos == str_length) {
                // Have matched a copy of search string
                count++;
                str_pos = table[str_pos - 1];
            } else if (offset < new_bytes) {
                // Have reached a mismatch
                if (str_pos != 0) {
                    str_pos = table[str_pos - 1];
                } else {
                    offset++;
                }
            } /* else {
                // Have reached end of buffer
                //   Do nothing, allow new buffer to be read in from file
            } */
        }

        bytes_read += new_bytes;
    }

    free(table);
    return count;
}

void fillLPSTable(const char* string, size_t table[], size_t length) {
    // An implementation of the Knuth-Morris-Pratt algorithm as
    // described in Introduction to Algorithms by CLRS.

    table[0] = 0;   // Single character has no proper prefix

    for (size_t curr_pos = 1; curr_pos < length; curr_pos++) {
        // Now working only with string[0..curr_pos]

        // Check for proper prefixes with length >= 2
        //   that are also suffixes
        // These can be decomposed into a proper prefix-suffix
        //   of string[0..curr_pos-1] that can be extended by a match
        size_t prev_lps = table[curr_pos - 1];
        while ((prev_lps > 0) && (string[curr_pos] != string[prev_lps])) {
            prev_lps = table[prev_lps - 1];
        }

        // At this point, either
        //   string[curr_pos] == string[prev_lps] ->                    (lps at curr_pos extends prev_lps by 1)
        //   string[curr_pos] != string[prev_lps] && prev_lps == 0 ->   (lps at curr_pos is 0)
        if (string[curr_pos] == string[prev_lps]) {
            table[curr_pos] = prev_lps + 1;
        } else {
            table[curr_pos] = 0;
        }
    }
}
