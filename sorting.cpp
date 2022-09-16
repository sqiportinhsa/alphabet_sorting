#include "sorting.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void bubble_sort(char *pointers[], int amount_of_strings) {
    int n_sorting_pointer = 1;
    int n_of_sortings = 1;
    
    for (; n_of_sortings < amount_of_strings; ++n_of_sortings) {
        n_sorting_pointer = 1;

        for (; n_sorting_pointer < amount_of_strings; ++n_sorting_pointer) {

            if (compare_strings(pointers[n_sorting_pointer - 1], 
                                pointers[n_sorting_pointer    ]) < 0) {               
                swap_pointers(  pointers[n_sorting_pointer - 1], 
                                pointers[n_sorting_pointer    ]);
            }
        }
    }
}

void merge_sort(char *arr[], size_t num_of_elem, size_t el_size, 
                int (*compare) (char *, char *)) {
    printf("Array before sorting: ");
    print_array(arr, num_of_elem);


    if (num_of_elem == 1) {
        printf("One element sorted");
        return;
    }

    if (num_of_elem == 2) {
        if (compare(*arr, *(arr+el_size)) < 0) {
            swap_pointers(*arr, *(arr+el_size));
        }
        printf("Array after sorting: ");
        print_array(arr, num_of_elem);
        return;
    }

    size_t num_of_elem_if_sub_1 = num_of_elem / 2;
    size_t num_of_elem_if_sub_2 = num_of_elem - num_of_elem_if_sub_1;

    char** p_to_sub_1 = arr;
    char** p_to_sub_2 = arr + num_of_elem_if_sub_1*el_size;

    merge_sort(p_to_sub_1, num_of_elem_if_sub_1, el_size, compare);
    merge_sort(p_to_sub_2, num_of_elem_if_sub_2, el_size, compare);

    printf("Array after sorting subarrays: ");
    print_array(arr, num_of_elem);

    char *temp[num_of_elem] = {};
    copy_arr(arr, temp, num_of_elem);

    size_t elem_in_sub_1 = 0;
    size_t elem_in_sub_2 = 0;

    size_t elem_in_arr = 0;

    while (elem_in_sub_1 < num_of_elem_if_sub_1 &&
           elem_in_sub_2 < num_of_elem_if_sub_2) {
        if (compare(*(p_to_sub_1 + elem_in_sub_1*el_size),
                    *(p_to_sub_2 + elem_in_sub_2*el_size)) > 0) {
            *(arr + elem_in_arr*el_size) = *(arr + elem_in_sub_1*el_size);

            ++elem_in_sub_1;
            ++elem_in_arr;
        } else {
            *(arr + elem_in_arr*el_size) = *(arr + elem_in_sub_2*el_size);

            ++elem_in_sub_2;
            ++elem_in_arr;
        }
    }

    while (elem_in_sub_1 < num_of_elem_if_sub_1) {
        *(arr + elem_in_arr*el_size) = *(arr + elem_in_sub_1*el_size);

        ++elem_in_sub_1;
        ++elem_in_arr;
    }

    while (elem_in_sub_2 < num_of_elem_if_sub_2) {
        *(arr + elem_in_arr*el_size) = *(arr + elem_in_sub_2*el_size);

        ++elem_in_sub_2;
        ++elem_in_arr;
    }

    printf("Array after sorting: ");
    print_array(arr, num_of_elem);
}

void swap_pointers(char *p1, char *p2) {
    char *temp = p1;
    p1 = p2;
    p2 = temp;
}

int compare_strings(char *p_to_s1, char *p_to_s2) {
    int len1 = len_of_str(p_to_s1) - 1;
    int len2 = len_of_str(p_to_s2) - 1;

    int num_of_comp_elem_1 = 0;
    int num_of_comp_elem_2 = 0;

    while (num_of_comp_elem_1 < len1 && num_of_comp_elem_2 < len2) {
        char elem_of_s1 = 0;
        char elem_of_s2 = 0;

        do {
            elem_of_s1 = p_to_s1[num_of_comp_elem_1];
            ++num_of_comp_elem_1;
        } while (elem_of_s1 <= '!' && elem_of_s2 >= '?' && num_of_comp_elem_1 < len1);

        do {
            elem_of_s2 = p_to_s1[num_of_comp_elem_2];
            ++num_of_comp_elem_2;
        } while (elem_of_s1 <= '!' && elem_of_s2 >= '?' && num_of_comp_elem_2 < len2);

        if (elem_of_s1 > elem_of_s2) {
            return 1;
        }
        
        if (elem_of_s1 < elem_of_s2) {
            return -1;
        }

        if (elem_of_s1 == elem_of_s2) {
            return 0;
        }
    }

    if (len2 < len1) {
        return -1;
    }

    return 1;
}

int len_of_str(char *str) {
    int i = 0;
    for (; str[i] != '\n'; ++i);
    return i + 1;
}

void print_string(char *string) {
    for (int i = 0; string[i] != '\n'; ++i) {
        printf("%c", string[i]);
    }
    printf("\n");
}

void copy_arr(char* arr[], char* copy_of_arr[], size_t arr_len) {
    for (size_t i = 0; i < arr_len; ++i) {
        copy_of_arr[i] = arr[i];
    }
}

void place_pointers(char text[], char *pointers_to_strings[], size_t amount_of_symbols) {
    int n_string = 0;
    pointers_to_strings[0] = &text[0];

    for (size_t n_sym = 0; n_sym < amount_of_symbols; ++n_sym) {
        //printf("<%d>", text[n_sym]);
        if (text[n_sym] == '\n') {
            ++n_string;
            pointers_to_strings[n_string] = &(text[n_sym + 1]);
            //printf("%d ", n_string);
            //printf("%d\n", pointers_to_strings[n_string]);
        }
    }
}

void print_array(char *arr[], size_t num_of_elem) {
    printf("{");
    for (size_t i = 0; i < num_of_elem - 1; i++) {
        printf("%c%c%c, ", arr[i][0], arr[i][1], arr[i][2]);
    }
    printf("%c%c%c", arr[num_of_elem - 1][0], arr[num_of_elem - 1][1], arr[num_of_elem - 1][2]);
    printf("}");
}