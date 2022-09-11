#include <stdio.h>
#include <sys/stat.h>
#include "sorting.h"


int main() {
    struct stat a = {};
    stat("onegin.txt", &a);
    size_t amount_of_symbols = a.st_size;

    char onegin[amount_of_symbols] = {};

    FILE *input = fopen("onegin.txt", "r");

    int c = '0';
    int amount_of_strings = 0;

    for (size_t i = 0; i < amount_of_symbols && (c = getc(input)) != EOF; ++i) {
        onegin[i] = (char) c;
        if (onegin[i] == '\n') {
            ++c;
        }
    }

    printf("%d\n", amount_of_strings);

    fclose(input);

    for (int i = 0; i <101; ++i) {
        printf("%c", onegin[i]);
    }

    char *pointers_to_strings[amount_of_strings] = {};
    int n_string = 0;

    //printf("%hhn", pointers_to_strings[1]);
    //printf("%hhn", pointers_to_strings[2]);

    for (size_t n_sym = 0; n_sym < amount_of_symbols; ++n_sym) {
        printf(".");
        if (onegin[n_sym] == '\n') {
            pointers_to_strings[n_string] = &(onegin[n_sym]);
            ++n_string;
            printf("\n");
        }
    }

    //printf("<%c>", pointers_to_strings[1][0]);

    bubble_sort(pointers_to_strings, amount_of_strings);

    FILE *output = fopen("sorted_onegin.txt", "w");

    for (int n_str = 0; n_str < amount_of_strings; ++n_str) {
        size_t len_of_str = strlen(pointers_to_strings[n_str]);

        for (size_t i = 0; i < len_of_str; ++i) {
            putc(pointers_to_strings[n_str][i], output);
        }
    }

    fclose(output);

    return 0;
}