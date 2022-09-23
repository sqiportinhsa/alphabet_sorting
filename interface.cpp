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
            printf("incorrect input: length of file names should be less than %lld", 
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

            printf("incorrect input: length of file names should be less than %lld", 
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

size_t read_text(char text[], size_t amount_of_symbols, FILE *input) {
    size_t nread = fread(text, sizeof(char), amount_of_symbols, input);

    size_t real_amount_of_symbols = nread + 1;
    text[real_amount_of_symbols - 1] = '\n';

    return real_amount_of_symbols;
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

void place_pointers(struct String strings[], char *text, size_t amount_of_symbols, 
                                                            int amount_of_strings) {
    strings[0].ptr = &(text[0]);
    int nstring = 0;
    size_t nsym = 0;

    for (; nstring < amount_of_strings - 1; ++nsym) {
        if (text[nsym] == '\n') {
            ++nstring;
            strings[nstring].ptr = &(text[nsym + 1]);

            strings[nstring - 1].len = (int) (strings[nstring - 0].ptr -
                                              strings[nstring - 1].ptr);
        }
    }

    strings[amount_of_strings - 1].len = (int) (amount_of_symbols - nsym);
}

void write_text_by_strings(FILE *output, struct String strings[], int amount_of_strings) {
    for (int n_str = 0; n_str < amount_of_strings; ++n_str) {
        if (*((strings[n_str]).ptr) == '\n') {
            continue;
        }

        for (int i = 0; *((strings[n_str]).ptr + i) != '\n'; ++i) {
            putc(*((strings[n_str]).ptr + i), output);
        }

        putc('\n', output);
    }
}

void write_text_by_chars(FILE *output, char text[], size_t amount_of_symbols) {
    for (size_t i = 0; i < amount_of_symbols - 1; ++i) {
        putc(text[i], output);
    }
}

size_t elements_in_file(char file_name[]) {
    struct stat a = {};
    stat(file_name, &a);
    return a.st_size;
}

void print_string(char *string) {
    for (int i = 0; string[i] != '\n'; ++i) {
        printf("%c", string[i]);
    }
    printf("\n");
}

void print_strings(struct String *strings, size_t amount_of_strings) {
    for (size_t i = 0; i < amount_of_strings; ++i) {
        printf("String number %lld (length %lld):", i, (strings[i]).len);
        print_string((strings[i]).ptr);
    }
    printf("All strings printed.\n");
}
