#include "interface.h"

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "common.h"

const char Default_file_flag[] = "-d";
const char default_input[]  = "onegin.txt";
const char default_output[] = "sorted.txt";

int get_file_names(int argc, const char *argv[], char input_file[], char output_file[]) {
    if (argc == 1) {
        strcpy( input_file, default_input);
        strcpy(output_file, default_output);
        return 0;
    }

    if (argc == 2) {
        if (strlen(argv[1]) > max_len_of_filename) {
            printf("incorrect input: length of file names should be less than %d", 
                                                              max_len_of_filename);
            return -1;
        }

        if (!strcmp(argv[1], Default_file_flag)) {
            strcpy( input_file, default_input);
        } else {
            strcpy( input_file, argv[1]);
        }
        strcpy(output_file, default_output);
        return 0;
    }

    if (argc == 3) {
        if (strlen(argv[1]) > max_len_of_filename || 
            strlen(argv[2]) > max_len_of_filename) {

            printf("incorrect input: length of file names should be less than %d", 
                                                              max_len_of_filename);
            return -1;
        }

        if (!strcmp(argv[1], Default_file_flag)) {
            strcpy(input_file, default_input);
        } else {
            strcpy(input_file, argv[1]);
        }

        if (!strcmp(argv[2], Default_file_flag)) {
            strcpy(output_file, default_output);
        } else {
            strcpy(output_file, argv[2]);
        }

        return 0;
    }

    printf("incorrect input: expected names of input and output files or \"-d\" for default");
    return 1;
}

void write_text(FILE *output, char *text[], int amount_of_strings) {
    for (int n_str = 0; n_str < amount_of_strings; ++n_str) {
        if (text[n_str][0] == '\n') {
            continue;
        }

        for (int i = 0; text[n_str][i] != '\n'; ++i) {
            putc(text[n_str][i], output);
        }

        putc('\n', output);
    }
}

size_t elements_in_file(char file_name[]) {
    struct stat a = {};
    stat(file_name, &a);
    return a.st_size;
}

int count_strings(char text[], size_t amount_of_symbols) {
    int amount_of_strings = 0;
    for (size_t i = 0; i < amount_of_symbols; ++i) {
        if (text[i] == '\n') {
            ++amount_of_strings;
        }
    }
    return amount_of_strings;
}

size_t read_text(char text[], size_t amount_of_symbols, FILE *input) {
    size_t nread = fread(text, sizeof(char), amount_of_symbols, input);

    size_t real_amount_of_symbols = nread + 1;
    text[real_amount_of_symbols - 1] = '\n';

    return real_amount_of_symbols;
}

void place_pointers(struct String strings[], char *text, size_t amount_of_symbols, 
                                                            int amount_of_strings) {
    strings[0].ptr_to_start = &(text[0]);
    int nstring = 0;
    size_t nsym = 0;

    for (; nstring < amount_of_strings - 1; ++nsym) {
        if (text[nsym] == '\n') {
            ++nstring;
            strings[nstring].ptr_to_start = &(text[nsym + 1]);

            strings[nstring - 1].len_of_str = (int) (strings[nstring - 0].ptr_to_start -
                                                     strings[nstring - 1].ptr_to_start);
        }
    }

    strings[amount_of_strings - 1].len_of_str = (int) (amount_of_symbols - nsym);
}
