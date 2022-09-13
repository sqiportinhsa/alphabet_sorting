#include <stdio.h>
#include <sys/stat.h>
#include "sorting.h"


int main() {
    struct stat a = {};
    stat("onegin.txt", &a);
    size_t amount_of_symbols = a.st_size;

    char onegin[amount_of_symbols + 1] = {};

    FILE *input = fopen("onegin.txt", "r");

    int c = '0';
    int amount_of_strings = 0;

    for (size_t i = 0; i < amount_of_symbols && (c = getc(input)) != EOF; ++i) {
        onegin[i] = (char) c;
        if (onegin[i] == '\n') {
            ++amount_of_strings;
            //printf("%c", onegin[i-1]); print the last symbol of string
        }
    }

    onegin[amount_of_symbols] = '\n';
    ++amount_of_strings;

    for (size_t i = 0; i <= amount_of_symbols; ++i) {
        printf("<%c>", onegin[i]);
    }

    //printf("<%c>", onegin[amount_of_symbols - 23]);

    //printf("%d\n", amount_of_strings);

    fclose(input);

    char *pointers_to_strings[amount_of_strings + 1] = {};
    int n_string = 0;

    for (size_t n_sym = 0; n_sym < amount_of_symbols; ++n_sym) {
        //printf("%c", onegin[n_sym]);
        if (onegin[n_sym] == '\n') {
            ++n_string;
            pointers_to_strings[n_string] = &(onegin[n_sym + 1]);
            printf("%d ", n_string);
        }
    }

    FILE *output = fopen("sorted_onegin.txt", "w");

    for (int n_str = 0; n_str < amount_of_strings; ++n_str) {
        for (int i = 0; pointers_to_strings[n_str][i] != '\n'; ++i) {
            putc(pointers_to_strings[n_str][i], output);
        }
        putc('\n', output);

        print_string(pointers_to_strings[n_str]);
    }

    fclose(output);

    //printf("<%c>", pointers_to_strings[0][0]);

    bubble_sort(pointers_to_strings, amount_of_strings);

    return 0;
}