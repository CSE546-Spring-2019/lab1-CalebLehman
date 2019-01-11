#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "naive.h"

Counts countNaive(FILE* file, const char* string) {
    Counts counts;

    counts.count_matches = 0;
    size_t str_length = strlen(string);

    char buffer[MAX_CHUNK];         // A buffer to store bytes read from file
    size_t shift = MAX_CHUNK;       // Amount to shift buffer by before next read from file
    counts.count_bytes = 0;         // Tracks the number of positions in file that have been checked as
                                    //   potential starting position for match

    // Loop over file, reading into buffer
    int finished_reading = 0;
    while (!finished_reading) {
        size_t bytes_read;  // Number of bytes read from file this iteration
        size_t buffer_size; // Size of buffer (non-garbage values)

        // Shift buffer to left and read new bytes from file
        memmove(buffer, buffer + shift, MAX_CHUNK - shift);
        bytes_read = fread(buffer + MAX_CHUNK - shift, sizeof(char), shift, file);
        buffer_size = MAX_CHUNK - shift + bytes_read;

        // Check each position in buffer as starting position for match
        for (size_t offset = 0; offset + str_length < buffer_size; offset++) {
            if (memcmp(string, buffer + offset, str_length) == 0) {
                counts.count_matches++;
            }
            /*
            if (lengthOfCommonPrefix(string, str_length, buffer + offset, buffer_size - offset) == str_length) {
                count++;
            }
            */
        }

        // Shift processed bytes out of buffer, keeping last str_length + 1
        shift = MAX_CHUNK - str_length + 1;
        counts.count_bytes += bytes_read;
        finished_reading = feof(file);
    }
    
    return counts;
}
