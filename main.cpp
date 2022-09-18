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

    char *sort_from_beg_ptrs[amount_of_strings + 1] = {};
    place_pointers(text, sort_from_beg_ptrs, amount_of_symbols);

    char *sort_from_end_ptrs[amount_of_strings + 1] = {};
    place_pointers(text, sort_from_end_ptrs, amount_of_symbols);

    merge_sort((void**) sort_from_beg_ptrs, amount_of_strings, 1, compare_strings);
    merge_sort((void**) sort_from_end_ptrs, amount_of_strings, 1, reversed_comparator);

    FILE *output = fopen("sorted_onegin.txt", "w");

    fputs("File sorted in alphabet order:\n\n", output);

    for (int n_str = 0; n_str < amount_of_strings; ++n_str) {
        if (sort_from_beg_ptrs[n_str][0] == '\n') {
            continue;
        }

        for (int i = 0; sort_from_beg_ptrs[n_str][i] != '\n'; ++i) {
            //printf("<%c>", sort_from_beg_ptrs[n_str][i]);
            putc(sort_from_beg_ptrs[n_str][i], output);
        }
        putc('\n', output);
    }

    fputs("\n\nFile sorted in alphabet order by last letters:\n\n", output);

    for (int n_str = 0; n_str < amount_of_strings; ++n_str) {
        if (sort_from_end_ptrs[n_str][0] == '\n') {
            continue;
        }

        for (int i = 0; sort_from_end_ptrs[n_str][i] != '\n'; ++i) {
            //printf("<%c>", sort_from_beg_ptrs[n_str][i]);
            putc(sort_from_end_ptrs[n_str][i], output);
        }
        putc('\n', output);
    }

    fputs("\n\nOriginal text:\n\n", output);

    for (size_t i = 0; i < amount_of_symbols; ++i) {
        putc(text[i], output);
    }

    fclose(output);

    printf("Sorting is done!\nThanks for using this sorter!\n");

    return 0;
}