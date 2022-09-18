#include <stdio.h>
#include <sys/stat.h>
#include "sorting.h"


int main() {
    struct stat a = {};
    stat("onegin.txt", &a);
    size_t amount_of_symbols = a.st_size;

    char text[amount_of_symbols + 1] = {};

    FILE *input = fopen("onegin.txt", "r");

    int amount_of_strings = 0;

    int c = '0';
    for (size_t i = 0; i < amount_of_symbols && (c = getc(input)) != EOF; ++i) {
        text[i] = (char) c;
        if (text[i] == '\n') {
            ++amount_of_strings;
        }
    }

    amount_of_symbols -= amount_of_strings;
    text[amount_of_symbols] = '\n';
    ++amount_of_strings;

    fclose(input);

    char *pointers_to_strings[amount_of_strings + 1] = {};
    place_pointers(text, pointers_to_strings, amount_of_symbols);

    merge_sort((void**) pointers_to_strings, amount_of_strings, 1, compare_strings);

    FILE *output = fopen("sorted_onegin.txt", "w");

    for (int n_str = 0; n_str < amount_of_strings; ++n_str) {
        for (int i = 0; pointers_to_strings[n_str][i] != '\n'; ++i) {
            //printf("<%c>", pointers_to_strings[n_str][i]);
            putc(pointers_to_strings[n_str][i], output);
        }
        putc('\n', output);
    }

    fclose(output);

    return 0;
}