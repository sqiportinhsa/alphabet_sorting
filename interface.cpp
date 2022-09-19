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
        if (strlen(argv[1]) > 50) {
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
        if (strlen(argv[1]) > 50 || strlen(argv[2]) > 50) {
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
