/**
 * Author: Caleb Lehman (lehman.346@osu.edu)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "defs.h"
#include "kmp.h"
#include "naive.h"

const size_t MAX_CHUNK = 100;
const size_t MAX_SEARCH_STR_LEN = 20;

int main(int argc, char *argv[]) {
    // Check that program was run with proper amount of arguments
    if (argc != 4) {
        printf("Program requires 3 arguments, received %d\n", argc - 1);
        printf("Usage is count <input-filename> <search-string> <output-filename>\n");
        printf("Exiting...\n");
        exit(1);
    }

    const char* input_filename  = argv[1];
    const char* search_string   = argv[2];
    const char* output_filename = argv[3];

    // Check that search string has valid length
    size_t str_length = strlen(search_string);
    if (strlen(search_string) == 0) {
        printf("Cannot search for 0-length string.\nExiting...\n");
        exit(1);
    } else if (str_length > MAX_SEARCH_STR_LEN) {
        printf("Cannot search for a string of length > %ld.\nExiting...\n", MAX_SEARCH_STR_LEN);
        exit(1);
    }

    // Open files and check for success
    FILE* in_file   = fopen(input_filename, "rb");
    FILE* out_file  = fopen(output_filename, "w");
    if (in_file == NULL) {
        printf("Could not open input file: %s\nExiting...\n", input_filename);
        exit(1);
    }
    if (out_file == NULL) {
        printf("Could not open output file: %s\nExiting...\n", output_filename);
        exit(1);
    }


    Counts counts;
#ifdef NAIVE
    counts = countNaive(in_file, search_string);
#else
    counts = countKnuthMorrisPratt(in_file, search_string);
#endif

    // Print counts to stdout and output file
    printf("Size of file is %llu\n", counts.count_bytes);
    fprintf(out_file, "Size of file is %llu\n", counts.count_bytes);

    printf("Number of matches = %llu\n", counts.count_matches);
    fprintf(out_file, "Number of matches = %llu\n", counts.count_matches);

    // Close files
    fclose(in_file);
    fclose(out_file);

    return 0;
}
