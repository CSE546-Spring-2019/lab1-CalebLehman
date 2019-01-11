#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "defs.h"
#include "kmp.h"
#include "naive.h"

const size_t MAX_CHUNK = 100;

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

    // Check that search string has non-zero length
    if (strlen(search_string) == 0) {
        printf("Cannot search for 0-length string.\nExiting...\n");
        exit(1);
    }

    // Open files
    FILE* in_file   = fopen(input_filename, "rb");
    FILE* out_file  = fopen(output_filename, "w");

    // Check that files are open
    if (in_file == NULL) {
        printf("Could not open input file: %s\nExiting...\n", input_filename);
        exit(1);
    }
    if (out_file == NULL) {
        printf("Could not open output file: %s\nExiting...\n", output_filename);
        exit(1);
    }

    // Count bytes in file
    fseek(in_file, 0, SEEK_END);
    long int file_length = ftell(in_file);
    fseek(in_file, 0, SEEK_SET);
    printf("Size of file is %ld\n", file_length);
    fprintf(out_file, "Size of file is %ld\n", file_length);

    // Count occurrences of string
    size_t count;
#ifdef NAIVE
    count = countSlidingWindow(in_file, file_length, search_string);
#else
    count = countKnuthMorrisPratt(in_file, file_length, search_string);
#endif // NAIVE
    printf("Number of matches = %ld\n", count);
    fprintf(out_file, "Number of matches = %ld\n", count);

    // Close files
    fclose(in_file);
    fclose(out_file);

    return 0;
}