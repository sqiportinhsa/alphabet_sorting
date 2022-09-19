#include "sorting.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cassert>
#include <cctype>
#include "common.h"

void bubble_sort(char *pointers[], int amount_of_strings) {
    int n_sorting_pointer = 1;
    int n_of_sortings = 1;
    
    for (; n_of_sortings < amount_of_strings; ++n_of_sortings) {
        n_sorting_pointer = 1;

        for (; n_sorting_pointer < amount_of_strings; ++n_sorting_pointer) {

            if (compare_strings(pointers[n_sorting_pointer - 1], 
                                pointers[n_sorting_pointer    ]) < 0) {               
                swap_pointers( &pointers[n_sorting_pointer - 1], 
                               &pointers[n_sorting_pointer    ]);
            }
        }
    }
}

void merge_sort(void *array[], size_t num_of_elem, size_t el_size, 
                int (*compare) (void *, void *)) {
    char **arr = (char**) array;
    //printf("Array before sorting:          ");
    //print_array(arr, num_of_elem);


    if (num_of_elem == 1) {
        //printf("One element sorted\n");
        return;
    }

    if (num_of_elem == 2) {
        if (compare(*arr, *(arr + el_size)) < 0) {
            //printf("compatation done sucsessfull");
            swap_pointers(arr, (arr+el_size));
        }
        //printf("Array after  sorting:          ");
        //print_array(arr, num_of_elem);
        return;
    }

    size_t num_of_elem_if_sub_1 = num_of_elem / 2;
    size_t num_of_elem_if_sub_2 = num_of_elem - num_of_elem_if_sub_1;

    char** p_to_sub_1 = arr;
    char** p_to_sub_2 = arr + num_of_elem_if_sub_1*el_size;

    merge_sort((void**) p_to_sub_1, num_of_elem_if_sub_1, el_size, compare);
    merge_sort((void**) p_to_sub_2, num_of_elem_if_sub_2, el_size, compare);

    //printf("Array after sorting subarrays: ");
    //print_array(arr, num_of_elem);

    char *temp[num_of_elem * el_size] = {};
    copy_arr(arr, temp, num_of_elem);

    size_t elem_in_sub_1 = 0;
    size_t elem_in_sub_2 = 0;

    size_t elem_in_temp = 0;

    while (elem_in_sub_1 < num_of_elem_if_sub_1 &&
           elem_in_sub_2 < num_of_elem_if_sub_2) {
        //printf("least string in sub1 is string number %lld: ", elem_in_sub_1);
        //print_string(*(p_to_sub_1 + elem_in_sub_1*el_size));
        //printf("least string in sub2 is string number %lld: ", elem_in_sub_2);
        //print_string(*(p_to_sub_2 + elem_in_sub_2*el_size));

        if (compare(*(p_to_sub_1 + elem_in_sub_1*el_size),
                    *(p_to_sub_2 + elem_in_sub_2*el_size)) > 0) {
            //printf("least of them is: ");
            //print_string(*(p_to_sub_1 + elem_in_sub_1*el_size));
            *(temp + elem_in_temp*el_size) = *(p_to_sub_1 + elem_in_sub_1*el_size);

            ++elem_in_sub_1;
            ++elem_in_temp;
        } else {
            //printf("least of them is: ");
            //print_string(*(p_to_sub_2 + elem_in_sub_2*el_size));
            *(temp + elem_in_temp*el_size) = *(p_to_sub_2 + elem_in_sub_2*el_size);

            ++elem_in_sub_2;
            ++elem_in_temp;
        }

        //printf("Array after adding element: ");
        //print_array(temp, elem_in_temp + 1);
    }

    while (elem_in_sub_1 < num_of_elem_if_sub_1) {
        *(temp + elem_in_temp*el_size) = *(p_to_sub_1 + elem_in_sub_1*el_size);

        ++elem_in_sub_1;
        ++elem_in_temp;
    }

    while (elem_in_sub_2 < num_of_elem_if_sub_2) {
        *(temp + elem_in_temp*el_size) = *(p_to_sub_2 + elem_in_sub_2*el_size);

        ++elem_in_sub_2;
        ++elem_in_temp;
    }

    //printf("Sorted array:               ");
    //print_array(temp, num_of_elem);
    //printf("//----------------------------------------//\n");

    copy_arr(temp, arr, num_of_elem);
    //printf("Array after sorting:        ");
    //print_array(arr, num_of_elem);
}

void swap_pointers(char **p1, char **p2) {
    //printf("Sorting started\n");
    char *temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int compare_strings(void *ptr_to_s1, void *ptr_to_s2) {
    char *p_to_s1 = (char *) ptr_to_s1;
    char *p_to_s2 = (char *) ptr_to_s2;

    assert(p_to_s1 != nullptr);
    assert(p_to_s2 != nullptr);

    //printf("Compairing strings:\n");

    //print_string(p_to_s1);
    //print_string(p_to_s2);

    int len1 = len_of_str(p_to_s1) - 1;
    int len2 = len_of_str(p_to_s2) - 1;

    int num_of_comp_elem_1 = 0;
    int num_of_comp_elem_2 = 0;

    //printf("comparison started\n");

    while (num_of_comp_elem_1 < len1 && num_of_comp_elem_2 < len2) {
        char elem_of_s1 = next_letter_sym(p_to_s1, &num_of_comp_elem_1, len1);
        char elem_of_s2 = next_letter_sym(p_to_s2, &num_of_comp_elem_2, len2);

        /*if (abs(elem_of_s1 - elem_of_s2) == 'a' - 'A') {
            ++num_of_comp_elem_1;
            ++num_of_comp_elem_2;
            continue;
        } */
    
        //printf("element 1: %c\n", elem_of_s1);
        //printf("element 2: %c\n", elem_of_s2);

        if (elem_of_s1 > elem_of_s2) {
            //printf("-1\n");
            return -1;
        }
        
        if (elem_of_s1 < elem_of_s2) {
            //printf("1\n");
            return 1;
        }

        //printf("elements are simular, comparing next:\n");

        ++num_of_comp_elem_1;
        ++num_of_comp_elem_2;
    }

    if (len2 < len1) {
        //printf("-1\n");
        return -1;
    }

    if (len1 < len2) {
        //printf("1\n");
        return  1;
    }

    //printf("0");
    return 0;
}

int reversed_comparator(void *ptr_to_s1, void *ptr_to_s2) {
    char *p_to_s1 = (char *) ptr_to_s1;
    char *p_to_s2 = (char *) ptr_to_s2;

    assert(p_to_s1 != nullptr);
    assert(p_to_s2 != nullptr);

    //printf("Compairing strings:\n");

    //print_string(p_to_s1);
    //print_string(p_to_s2);

    int len1 = len_of_str(p_to_s1);
    int len2 = len_of_str(p_to_s2);

    int num_of_comp_elem_1 = len1 - 1;
    int num_of_comp_elem_2 = len2 - 1;

    //printf("comparison started");

    while (num_of_comp_elem_1 >= 0 && num_of_comp_elem_2 >= 0) {
        char elem_of_s1 = prev_letter_sym(p_to_s1, &num_of_comp_elem_1);
        char elem_of_s2 = prev_letter_sym(p_to_s2, &num_of_comp_elem_2);

        //printf("element 1 with number %d: %c\n", num_of_comp_elem_1, elem_of_s1);
        //printf("element 2 with number %d: %c\n", num_of_comp_elem_2, elem_of_s2);

        if (elem_of_s1 > elem_of_s2) {
            //printf("-1\n");
            return -1;
        }
        
        if (elem_of_s1 < elem_of_s2) {
            //printf("1\n");
            return 1;
        }

        //printf("elements are simular, comparing next:\n");

        --num_of_comp_elem_1;
        --num_of_comp_elem_2;
    }

    if (len2 < len1) {
        //printf("-1");
        return -1;
    }

    if (len1 < len2) {
        //printf("1");
        return  1;
    }

    //printf("0");
    return 0;
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
    printf("}\n");
}

char next_letter_sym(const char str[], int* p_to_num_of_sym, int len) {
    char sym = str[*p_to_num_of_sym];
    
    while (isalpha(sym) == 0 && *p_to_num_of_sym < len - 1) {
        ++(*p_to_num_of_sym);
        sym = str[*p_to_num_of_sym];
    }

    return(sym);
}

char prev_letter_sym(const char str[], int* p_to_num_of_sym) {
    char sym = str[*p_to_num_of_sym];
    
    while (isalpha(sym) == 0 && *p_to_num_of_sym > 0) {
        --(*p_to_num_of_sym);
        sym = str[*p_to_num_of_sym];
    }

    return(sym);
}
