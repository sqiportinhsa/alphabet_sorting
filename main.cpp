#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"
#include "interface.h"
#include "common.h"

int main(int argc, const char **argv) {
    char  input_name[max_len_of_filename] = {};
    char output_name[max_len_of_filename] = {};

    int corr = get_file_names(argc, argv, input_name, output_name);

    if (corr < 0) {
        printf("incorrect input: length of file names should be less than %d", max_len_of_filename);
        return -1;
    }
    
    if (corr > 0) {
        printf("incorrect input: expected names of input and output files or \"-d\" for default");
        return - 1;
    }

    size_t amount_of_symbols = elements_in_file(input_name);

    char *text = (char*) calloc(amount_of_symbols, sizeof(char));

    if (text == nullptr) {
        printf("input error: input file is too large");
    }

    FILE *input = fopen(input_name, "r");

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

    FILE *output = fopen(output_name, "w");

    fputs("File sorted in alphabet order:\n\n", output);
    write_text(output, sort_from_beg_ptrs, amount_of_strings);

    fputs("\n\nFile sorted in alphabet order by last letters:\n\n", output);
    write_text(output, sort_from_end_ptrs, amount_of_strings);

    fputs("\n\nOriginal text:\n\n", output);

    for (size_t i = 0; i < amount_of_symbols; ++i) {
        putc(text[i], output);
    }

    fclose(output);

    printf("Sorting is done!\nThanks for using this sorter!\n");

    return 0;
}
