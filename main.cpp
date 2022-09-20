#include <stdio.h>
#include <stdlib.h>
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

    /*if (text == nullptr) {
        printf("input error: input file is too large");
    }*/

    FILE *input = fopen(input_name, "r");

    amount_of_symbols = read_text(text, amount_of_symbols, input);
    amount_of_strings = count_strings(text, amount_of_symbols);

    fclose(input);

    for (size_t i = 0; i < amount_of_symbols; ++i) {
        printf("<%c>", text[i]);
    }

    struct String left__to_rigth_sorted[amount_of_strings] = {};
    struct String right_to_left__sorted[amount_of_strings] = {};

    place_pointers(left__to_rigth_sorted, text, amount_of_symbols, amount_of_strings);
    place_pointers(right_to_left__sorted, text, amount_of_symbols, amount_of_strings);

    /*for (int i = 0; i < amount_of_strings; ++i) {
        printf("len of string num %d is %d, first element is <%c>\n", i,
                left__to_rigth_sorted[i].len_of_str, *(left__to_rigth_sorted[i].ptr_to_start));
    } */

    /*char *sort_from_beg_ptrs[amount_of_strings + 1] = {};
    place_pointers(text, sort_from_beg_ptrs, amount_of_symbols);

    char *sort_from_end_ptrs[amount_of_strings + 1] = {};
    place_pointers(text, sort_from_end_ptrs, amount_of_symbols);

    merge_sort((void**) sort_from_beg_ptrs, amount_of_strings, 1, compare_strings_ltor);
    merge_sort((void**) sort_from_end_ptrs, amount_of_strings, 1, compare_strings_rtol);

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

    printf("Sorting is done!\nThanks for using this sorter!\n"); */

    return 0;
}
