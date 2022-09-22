#include "sorting.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cassert>
#include <cctype>
#include "common.h"
#include "interface.h"

/*void bubble_sort(char *pointers[], int amount_of_strings) {
    int n_sorting_pointer = 1;
    int n_of_sortings = 1;
    
    for (; n_of_sortings < amount_of_strings; ++n_of_sortings) {
        n_sorting_pointer = 1;

        for (; n_sorting_pointer < amount_of_strings; ++n_sorting_pointer) {

            if (compare_strings_ltor(pointers[n_sorting_pointer - 1], 
                                     pointers[n_sorting_pointer    ]) < 0) {               
                swap_elements( &pointers[n_sorting_pointer - 1], 
                               &pointers[n_sorting_pointer    ]);
            }
        }
    }
}*/

void merge_sort(void *arr, size_t num_of_elem, size_t el_size, int (*compare) (void *, void *)) {
    char *array = (char*) arr;

    //printf("Array before sorting:\n");
    //print_strings(array, num_of_elem);

    if (num_of_elem == 1) {
        //printf("One element sorted\n");
        return;
    }

    if (num_of_elem == 2) {
        if (compare(array, (array + el_size)) < 0) {
            //printf("compatation done sucsessfull");
            swap_elements(array, (array + el_size), el_size);
        }
        //printf("Array after  sorting:\n");
        //print_strings(array, num_of_elem);
        return;
    }

    size_t num_of_elem_if_sub_1 = num_of_elem / 2;
    size_t num_of_elem_if_sub_2 = num_of_elem - num_of_elem_if_sub_1;

    char* p_to_sub_1 = array;
    char* p_to_sub_2 = array + num_of_elem_if_sub_1*el_size;

    merge_sort(p_to_sub_1, num_of_elem_if_sub_1, el_size, compare);
    merge_sort(p_to_sub_2, num_of_elem_if_sub_2, el_size, compare);

    //printf("Array after sorting subarrays:\n");
    //print_strings(array, num_of_elem);

    char temp[num_of_elem * el_size] = {};
    copy_arr(array, temp, num_of_elem, el_size);

    size_t elem_in_sub_1 = 0;
    size_t elem_in_sub_2 = 0;

    size_t elem_in_temp = 0;

    while (elem_in_sub_1 < num_of_elem_if_sub_1 &&
           elem_in_sub_2 < num_of_elem_if_sub_2) {
        //printf("least string in sub1 is string number %lld: ", elem_in_sub_1);
        //print_string(*(p_to_sub_1 + elem_in_sub_1*el_size));
        //printf("least string in sub2 is string number %lld: ", elem_in_sub_2);
        //print_string(*(p_to_sub_2 + elem_in_sub_2*el_size));

        if (compare((p_to_sub_1 + elem_in_sub_1*el_size),
                    (p_to_sub_2 + elem_in_sub_2*el_size)) > 0) {
            //printf("least of them is: ");
            //print_string(*(p_to_sub_1 + elem_in_sub_1*el_size));
            copy_arr(p_to_sub_1 + elem_in_sub_1*el_size, temp + elem_in_temp*el_size, 1, el_size);

            ++elem_in_sub_1;
            ++elem_in_temp;
        } else {
            //printf("least of them is: ");
            //print_string(*(p_to_sub_2 + elem_in_sub_2*el_size));
            copy_arr(p_to_sub_2 + elem_in_sub_2*el_size, temp + elem_in_temp*el_size, 1, el_size);

            ++elem_in_sub_2;
            ++elem_in_temp;
        }

        //printf("Array after adding element: ");
        //print_array(temp, elem_in_temp + 1);
    }

    while (elem_in_sub_1 < num_of_elem_if_sub_1) {
        copy_arr(p_to_sub_1 + elem_in_sub_1*el_size, temp + elem_in_temp*el_size, 1, el_size);
        
        ++elem_in_sub_1;
        ++elem_in_temp;
    }

    while (elem_in_sub_2 < num_of_elem_if_sub_2) {
        copy_arr(p_to_sub_2 + elem_in_sub_2*el_size, temp + elem_in_temp*el_size, 1, el_size);

        ++elem_in_sub_2;
        ++elem_in_temp;
    }

    //printf("Sorted array:               ");
    //print_array(temp, num_of_elem);
    //printf("//----------------------------------------//\n");

    copy_arr(temp, arr, num_of_elem, el_size);
    //printf("Array after sorting:        ");
    //print_array(arr, num_of_elem);
}

void swap_elements(void *p1, void *p2, size_t size_of_element) {
    char *ptr1 = (char*) p1;
    char *ptr2 = (char*) p2;

    //printf("Sorting started\n");

    char temp = 0;

    for (size_t i = 0; i < size_of_element; ++i) {
        copy_arr( ptr1 + i, &temp, 1, 1);
        copy_arr( ptr2 + i,  ptr1, 1, 1);
        copy_arr(&temp + i,  ptr1, 1, 1);
    }
}

int compare_strings_ltor(void *ptr_to_struct1, void *ptr_to_struct2) {
    struct String *p_to_s1 = (struct String*) ptr_to_struct1;
    struct String *p_to_s2 = (struct String*) ptr_to_struct2;

    assert(p_to_s1 != nullptr);
    assert(p_to_s2 != nullptr);

    //printf("Compairing strings:\n");

    //print_string(p_to_s1);
    //print_string(p_to_s2);

    int num_of_comp_elem_1 = 0;
    int num_of_comp_elem_2 = 0;

    //printf("comparison started\n");

    while (num_of_comp_elem_1 < (*p_to_s1).len && num_of_comp_elem_2 < (*p_to_s2).len) {
        char elem_of_s1 = next_letter_sym((*p_to_s1).ptr, &num_of_comp_elem_1, (*p_to_s1).len);
        char elem_of_s2 = next_letter_sym((*p_to_s2).ptr, &num_of_comp_elem_2, (*p_to_s2).len);

        /*if (isalpha(elem_of_s1 - dif_btw_cap_and_low)) {
            elem_of_s1 -= dif_btw_cap_and_low;
        }

        if (isalpha(elem_of_s2 - dif_btw_cap_and_low)) {
            elem_of_s2 -= dif_btw_cap_and_low;
        }*/
    
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

    if ((*p_to_s1).len < (*p_to_s2).len) {
        //printf("-1\n");
        return -1;
    }

    if ((*p_to_s1).len < (*p_to_s2).len) {
        //printf("1\n");
        return  1;
    }

    //printf("0");
    return 0;
}

int compare_strings_rtol(void *ptr_to_s1, void *ptr_to_s2) {
    struct String *p_to_s1 = (struct String *) ptr_to_s1;
    struct String *p_to_s2 = (struct String *) ptr_to_s2;

    assert(p_to_s1 != nullptr);
    assert(p_to_s2 != nullptr);

    //printf("Compairing strings:\n");

    //print_string(*(p_to_s1).ptr);
    //print_string(*(p_to_s2).ptr);

    int num_of_comp_elem_1 = (*p_to_s1).len - 1;
    int num_of_comp_elem_2 = (*p_to_s2).len - 1;

    //printf("comparison started");

    while (num_of_comp_elem_1 >= 0 && num_of_comp_elem_2 >= 0) {
        char elem_of_s1 = prev_letter_sym((*p_to_s1).ptr, &num_of_comp_elem_1);
        char elem_of_s2 = prev_letter_sym((*p_to_s2).ptr, &num_of_comp_elem_2);

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

    if ((*p_to_s1).len < (*p_to_s2).len) {
        //printf("-1");
        return -1;
    }

    if ((*p_to_s1).len < (*p_to_s2).len) {
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

void copy_arr(void *array, void *copy_of_array, size_t arr_len, size_t elem_size) {
    char         *arr = (char*)         array;
    char *copy_of_arr = (char*) copy_of_array;

    for (size_t n_elem = 0; n_elem < arr_len; ++n_elem) {
        for (size_t i = 0; i < elem_size; ++i) {
            *(copy_of_arr + n_elem*elem_size + i) = 
            *(        arr + n_elem*elem_size + i);
        }
    }
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
