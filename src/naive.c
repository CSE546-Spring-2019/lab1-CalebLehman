#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "naive.h"

size_t countSlidingWindow(FILE* file, long int file_length, const char* string) {
    size_t count = 0;
    size_t str_length = strlen(string);

    char buffer[MAX_CHUNK];         // A buffer to store bytes read from file
    size_t shift = MAX_CHUNK;       // Amount to shift buffer by before next read from file
    size_t file_pos_processed = 0;  // Number of positions in file that have been checked as
                                    //   potential starting position for match

    // Loop over file, reading into buffer
    while (file_pos_processed + str_length < file_length) {
        size_t bytes_read;  // Number of bytes read from file this iteration
        size_t buffer_size; // Size of buffer (non-garbage values)

        // Shift buffer to left and read new bytes from file
        memmove(buffer, buffer + shift, MAX_CHUNK - shift);
        bytes_read = fread(buffer + MAX_CHUNK - shift, sizeof(char), shift, file);
        buffer_size = MAX_CHUNK - shift + bytes_read;

        // Check each position in buffer as starting position for match
        for (size_t offset = 0; offset + str_length < buffer_size; offset++) {
            if (memcmp(string, buffer + offset, str_length) == 0) {
                count++;
            }
            /*
            if (lengthOfCommonPrefix(string, str_length, buffer + offset, buffer_size - offset) == str_length) {
                count++;
            }
            */
        }

        // Shift processed bytes out of buffer, keeping last str_length + 1
        shift = MAX_CHUNK - str_length + 1;
        file_pos_processed += buffer_size - str_length + 1;
    }

    return count;
}
