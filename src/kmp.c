/**
 * Author: Caleb Lehman (lehman.346@osu.edu)
 */

#include <string.h>
#include <stdlib.h>

#include "defs.h"
#include "kmp.h"

Counts countKnuthMorrisPratt(FILE* file, const char* string) {
    Counts counts;

    // Generate longest-prefix-suffix table
    size_t str_length = strlen(string);
    size_t table[MAX_SEARCH_STR_LEN];
    fillLPSTable(string, table, str_length);

    counts.count_matches = 0;

    char buffer[MAX_CHUNK]; // A buffer to store bytes read from file
    counts.count_bytes = 0; // Tracks total number of bytes read from file
    size_t str_pos = 0;     // Current position in search string
                            //   (previous positions have been matched)

    int finished_reading = 0;
    while (!finished_reading) {
        size_t bytes_read = fread(buffer, sizeof(char), MAX_CHUNK, file);

        size_t offset = 0;  // Offset within buffer
        while (offset < bytes_read) {
            // Match as far as possible starting from
            //   str_pos in search string and
            //   offset in buffer
            while ((str_pos < str_length) && (offset < bytes_read) && (string[str_pos] == buffer[offset])) {
                offset++;
                str_pos++;
            }

            // At this point, either
            //   have matched a copy of search string,
            //   have reached a mismatch, or
            //   have reached end of buffer
            if (str_pos == str_length) {
                counts.count_matches++;
                str_pos = table[str_pos - 1];
            } else if (offset < bytes_read) {
                if (str_pos == 0) {
                    // Failed to match any characters, move offset
                    offset++;
                } else {
                    // Matched some characters, set to longest prefix/suffix
                    str_pos = table[str_pos - 1];
                }
            }
        }

        counts.count_bytes+= bytes_read;
        finished_reading = feof(file);
    }

    return counts;
}

void fillLPSTable(const char* string, size_t* table, size_t length) {
    // An implementation of the prefix table in the Knuth-Morris-Pratt
    // algorithm as described in Introduction to Algorithms by CLRS.

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
        //   string[curr_pos] == string[prev_lps]                   -> (lps at curr_pos extends prev_lps by 1)
        //   string[curr_pos] != string[prev_lps] && prev_lps == 0  -> (lps at curr_pos is 0)
        if (string[curr_pos] == string[prev_lps]) {
            table[curr_pos] = prev_lps + 1;
        } else {
            table[curr_pos] = 0;
        }
    }
}
