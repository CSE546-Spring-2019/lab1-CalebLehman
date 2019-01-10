#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHUNK 100

/***************************************************************************
* Given two character arrays and their lengths, computes the length of the *
* longest prefix common to both strings.                                   *
****************************************************************************/
size_t lengthOfCommonPrefix(const char* str_1, size_t length_1, const char* str_2, size_t length_2);

/***************************************************************************
* Given a valid file pointer, the length of the file, and a string,        *
* returns a count of the number of occurrances of the string in the file.  *
* Counts using a sliding window approach, checking each position in the    *
* file as a possible start to a copy of the search string                  *
***************************************************************************/
size_t countSlidingWindow(FILE* file, long int file_length, const char* string);

/***************************************************************************
* Given a valid file pointer, the length of the file, and a string,        *
* returns a count of the number of occurrances of the string in the file.  *
* Counts using an adaptation of the Knuth-Morris-Pratt algorithm described *
* at https://en.wikipedia.org/wiki/Knuth-Morris-Pratt_algorithm.           *
***************************************************************************/
size_t countKnuthMorrisPratt(FILE* file, long int file_length, const char* string);
/***************************************************************************
* Given a string and table of the same length.                             *
* fills the table so that table[i] is the longest proper prefix of         *
* string[0..i] which is also a suffix of string[0..i].                     *
***************************************************************************/
void fillLPSTable(const char* string, size_t table[], size_t length);

int main(int argc, char *argv[]) {
    // Check that program was run with proper amount of arguments
    if (argc != 4) {
        printf("Program requires 3 arguments, received %d\n", argc - 1);
        printf("Run program with command: count <input-filename> <search-string> <output-filename>\n");
        printf("Exiting...");
        exit(1);
    }

    const char* input_filename  = argv[1];
    const char* search_string   = argv[2];
    const char* output_filename = argv[3];

    // Open files
    FILE* in_file   = fopen(input_filename, "rb");
    FILE* out_file  = fopen(output_filename, "w");

    // Check that files are open
    if (in_file == NULL) {
        printf("Could not open input file: %s\nExiting...", input_filename);
        exit(1);
    }
    if (out_file == NULL) {
        printf("Could not open output file: %s\nExiting...", output_filename);
        exit(1);
    }

    // Count bytes in file
    fseek(in_file, 0, SEEK_END);
    long int file_length = ftell(in_file);
    fseek(in_file, 0, SEEK_SET);
    printf("Size of file is %ld\n", file_length);
    fprintf(out_file, "Size of file is %ld\n", file_length);

    // Count occurrances of string
    // size_t count = countSlidingWindow(in_file, file_length, search_string);
    size_t count = countKnuthMorrisPratt(in_file, file_length, search_string);
    printf("Number of matches = %ld\n", count);
    fprintf(out_file, "Number of matches = %ld\n", count);

    // Close files
    fclose(in_file);
    fclose(out_file);

    return 0;
}

size_t lengthOfCommonPrefix(const char* str_1, size_t length_1, const char* str_2, size_t length_2) {
    size_t length = 0;

    // Iterate over strings until mismatch or end of a string
    while ((length < length_1) && (length < length_2) && (str_1[length] == str_2[length])) {
        length++;
    }

    return length;
}

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
            if (lengthOfCommonPrefix(string, str_length, buffer + offset, buffer_size - offset) == str_length) {
                count++;
            }
        }

        // Shift processed bytes out of buffer, keeping last str_length + 1
        shift = MAX_CHUNK - str_length + 1;
        file_pos_processed += buffer_size - str_length + 1;
    }

    return count;
}

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
            size_t match_length = lengthOfCommonPrefix(string + str_pos, str_length - str_pos, buffer + offset, new_bytes - offset); 
            offset += match_length;
            str_pos += match_length;

            // At this point, either
            //   have matched a copy of search string,
            //   have reached a mismatch, or
            //   have reached end of buffer
            if (str_pos == str_length) {
                // Have matched a copy of search string
                count++;
                str_pos = table[str_pos - 1];
            } else if ((offset < new_bytes) && (string[str_pos] != buffer[offset])) {
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
    // Simplified version of table construction from Knuth-Morris-Pratt
    //   algorithm as described at https://en.wikipedia.org/wiki/Knuth-Morris-Pratt_algorithm

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
