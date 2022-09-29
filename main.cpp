#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorting.h"
#include "interface.h"
#include "common.h"

int main(int argc, const char **argv) {
    char  input_name[max_len_of_filename] = {};
    char output_name[max_len_of_filename] = {};

    if(get_file_names(argc, argv, input_name, output_name) != 0) {
        return -1;
    }

    size_t amount_of_symbols = elements_in_file(input_name);
    int    amount_of_strings = 0;

    char *text = (char*) calloc(amount_of_symbols, sizeof(char));

    if (text == nullptr) {
        printf("input error: input file is too large");
        free(text);
        return -1;
    }

    FILE *input = fopen(input_name, "r");

    if (input == nullptr) {
        free(text);
        printf("Error: cannot open input file");
        return -1;
    }

    amount_of_symbols = read_text(text, amount_of_symbols, input);
    amount_of_strings = count_strings(text, amount_of_symbols);

    fclose(input);

    struct String *left__to_rigth_sorted = (struct String*) calloc(amount_of_strings, sizeof(String));
    struct String *right_to_left__sorted = (struct String*) calloc(amount_of_strings, sizeof(String));

    if (right_to_left__sorted == nullptr || left__to_rigth_sorted == nullptr) {
        printf("memory error: can't allocate enougth memory for sorting");
        free(right_to_left__sorted);
        free(left__to_rigth_sorted);
        free(text);
        return -1;
    }

    place_pointers(left__to_rigth_sorted, text, amount_of_symbols, amount_of_strings);

    memcpy(right_to_left__sorted, left__to_rigth_sorted, amount_of_strings * sizeof(String));

    int err = 0;

    err += merge_sort(left__to_rigth_sorted, amount_of_strings, sizeof(String), compare_strings_ltor);
    err += merge_sort(right_to_left__sorted, amount_of_strings, sizeof(String), compare_strings_rtol);

    if (err != 0) {
        printf("memory error: can't allocate enougth memory for sorting");
        free(right_to_left__sorted);
        free(left__to_rigth_sorted);
        free(text);
        return -1;
    }

    FILE *output = fopen(output_name, "w");

    if (output == nullptr) {
        printf("Error: cannot open output file");
        free(right_to_left__sorted);
        free(left__to_rigth_sorted);
        free(text);
        return -1;
    }

    fputs("File sorted in alphabet order from left to right:\n\n", output);
    write_text_by_strings(output, left__to_rigth_sorted, amount_of_strings);

    fputs("\n\nFile sorted in alphabet order from right to left:\n\n", output);
    write_text_by_strings(output, right_to_left__sorted, amount_of_strings);

    fputs("\n\nOriginal text:\n\n", output);
    fwrite(text, sizeof(char), amount_of_symbols - 1, output);

    fclose(output);

    free(text);
    free(left__to_rigth_sorted);
    free(right_to_left__sorted);

    printf("Sorting is done!\nThanks for using this sorter!\n");

    return 0;
}
