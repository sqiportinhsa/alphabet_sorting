#include "sorting.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cassert>
#include <cctype>
#include "common.h"
#include "interface.h"


void merge_sort(void *arr, size_t num_of_elem, size_t el_size, int (*compare) (void *, void *)) {
    char *array = (char*) arr;

    if (num_of_elem == 1) {
        DEBUG_PRINT("One element sorted\n");
        return;
    }

    DEBUG_PRINT("Array before sorting:\n");
    DEBUG_PRINT_STRINGS((String*) array, num_of_elem);

    char *temp = (char*) calloc(num_of_elem, el_size);

    merge_sort_internal(array, temp, num_of_elem, el_size, compare);

    memcpy(arr, temp, num_of_elem * el_size);
    free(temp);

    DEBUG_PRINT("Array after sorting:        ");
    DEBUG_PRINT_STRINGS((String*) arr, num_of_elem);
}

void merge_sort_internal(char *array, char* temp, size_t num_of_elem, 
                         size_t el_size, int (*compare) (void *, void *)) {
    DEBUG_PRINT("Array before sorting:\n");
    DEBUG_PRINT_STRINGS((String*) array, num_of_elem);

    if (num_of_elem == 1) {
        DEBUG_PRINT("One element sorted\n");
        return;
    }

    if (num_of_elem == 2) {
        if (compare(array, (array + el_size)) < 0) {
            DEBUG_PRINT("compatation done sucsessfull");
            swap_elements(array, (array + el_size), el_size);
        }
        DEBUG_PRINT("Array after  sorting:\n");
        DEBUG_PRINT_STRINGS((String*) array, num_of_elem);
        return;
    }

    size_t num_of_elem_if_sub_1 = num_of_elem / 2;
    size_t num_of_elem_if_sub_2 = num_of_elem - num_of_elem_if_sub_1;

    char* p_to_sub_1 = array;
    char* p_to_sub_2 = array + num_of_elem_if_sub_1*el_size;

    merge_sort_internal(p_to_sub_1, temp, num_of_elem_if_sub_1, el_size, compare);
    merge_sort_internal(p_to_sub_2, temp, num_of_elem_if_sub_2, el_size, compare);

    DEBUG_PRINT("Array after sorting subarrays:\n");
    DEBUG_PRINT_STRINGS((String*) array, num_of_elem);

    size_t elem_in_sub_1 = 0;
    size_t elem_in_sub_2 = 0;

    size_t elem_in_temp = 0;

    while (elem_in_sub_1 < num_of_elem_if_sub_1 &&
           elem_in_sub_2 < num_of_elem_if_sub_2) {
        DEBUG_PRINT("least string in sub1 is string number %lld: ", elem_in_sub_1);
        DEBUG_PRINT_STRING(((String*)(p_to_sub_1 + elem_in_sub_1*el_size))->ptr);
        DEBUG_PRINT("least string in sub2 is string number %lld: ", elem_in_sub_2);
        DEBUG_PRINT_STRING(((String*)(p_to_sub_2 + elem_in_sub_2*el_size))->ptr);

        if (compare((p_to_sub_1 + elem_in_sub_1*el_size),
                    (p_to_sub_2 + elem_in_sub_2*el_size)) > 0) {
            DEBUG_PRINT("least of them is: ");
            DEBUG_PRINT_STRING(((String*)(p_to_sub_1 + elem_in_sub_1*el_size))->ptr);
            memcpy(temp + elem_in_temp*el_size, p_to_sub_1 + elem_in_sub_1*el_size, el_size);

            ++elem_in_sub_1;
            ++elem_in_temp;
        } else {
            DEBUG_PRINT("least of them is: ");
            DEBUG_PRINT_STRING(((String*)(p_to_sub_2 + elem_in_sub_2*el_size))->ptr);
            memcpy(temp + elem_in_temp*el_size, p_to_sub_2 + elem_in_sub_2*el_size, el_size);

            ++elem_in_sub_2;
            ++elem_in_temp;
        }

        DEBUG_PRINT("\nArray after adding element: \n");
        DEBUG_PRINT_STRINGS((String*)temp, elem_in_temp);
    }

    while (elem_in_sub_1 < num_of_elem_if_sub_1) {
        memcpy(temp + elem_in_temp*el_size, p_to_sub_1 + elem_in_sub_1*el_size, el_size);
        
        ++elem_in_sub_1;
        ++elem_in_temp;
    }

    while (elem_in_sub_2 < num_of_elem_if_sub_2) {
        memcpy(temp + elem_in_temp*el_size, p_to_sub_2 + elem_in_sub_2*el_size, el_size);

        ++elem_in_sub_2;
        ++elem_in_temp;
    }

    memcpy(array, temp, num_of_elem*el_size);
    temp = {};

    DEBUG_PRINT("Array after sorting:        ");
    DEBUG_PRINT_STRINGS((String*) array, num_of_elem);

}

void swap_elements(void *p1, void *p2, size_t size_of_element) {
    char *ptr1 = (char*) p1;
    char *ptr2 = (char*) p2;

    DEBUG_PRINT("Sorting started\n");

    char temp = 0;

    for (size_t i = 0; i < size_of_element; ++i) {
        temp        = *(ptr1 + i);
        *(ptr1 + i) = *(ptr2 + i);
        *(ptr2 + i) = temp;
    }
}

int compare_strings_ltor(void *ptr_to_struct1, void *ptr_to_struct2) {
    struct String *p_to_s1 = (struct String*) ptr_to_struct1;
    struct String *p_to_s2 = (struct String*) ptr_to_struct2;

    assert(p_to_s1 != nullptr);
    assert(p_to_s2 != nullptr);

    DEBUG_PRINT("Compairing strings:\n");

    DEBUG_PRINT_STRING(p_to_s1->ptr);
    DEBUG_PRINT_STRING(p_to_s2->ptr);

    size_t num_of_comp_elem_1 = 0;
    size_t num_of_comp_elem_2 = 0;

    DEBUG_PRINT("comparison started\n");

    while (num_of_comp_elem_1 < p_to_s1->len && num_of_comp_elem_2 < p_to_s2->len) {
        char elem_of_s1 = next_letter_sym(p_to_s1->ptr, &num_of_comp_elem_1, p_to_s1->len);
        char elem_of_s2 = next_letter_sym(p_to_s2->ptr, &num_of_comp_elem_2, p_to_s2->len);
    
        DEBUG_PRINT("element 1: %c\n", elem_of_s1);
        DEBUG_PRINT("element 2: %c\n", elem_of_s2);

        int dif = elem_of_s2 - elem_of_s1;

        if (dif != 0) {
            DEBUG_PRINT("%d\n", dif);
            return dif;
        }

        DEBUG_PRINT("elements are simular, comparing next:\n");

        ++num_of_comp_elem_1;
        ++num_of_comp_elem_2;
    }

    size_t len_dif = p_to_s2->len - p_to_s1->len;

    DEBUG_PRINT("comp result: %lld", len_dif);

    return (int) len_dif;
}

int compare_strings_rtol(void *ptr_to_s1, void *ptr_to_s2) {
    struct String *p_to_s1 = (struct String *) ptr_to_s1;
    struct String *p_to_s2 = (struct String *) ptr_to_s2;

    assert(p_to_s1 != nullptr);
    assert(p_to_s2 != nullptr);

    DEBUG_PRINT("Compairing strings:\n");

    DEBUG_PRINT_STRING(p_to_s1->ptr);
    DEBUG_PRINT_STRING(p_to_s2->ptr);

    size_t num_of_comp_elem_1 = p_to_s1->len - 1;
    size_t num_of_comp_elem_2 = p_to_s2->len - 1;

    DEBUG_PRINT("comparison started");

    char elem_of_s1 = prev_letter_sym(p_to_s1->ptr, &num_of_comp_elem_1);
    char elem_of_s2 = prev_letter_sym(p_to_s2->ptr, &num_of_comp_elem_2);

    DEBUG_PRINT("element 1 with number %lld: %c\n", num_of_comp_elem_1, elem_of_s1);
    DEBUG_PRINT("element 2 with number %lld: %c\n", num_of_comp_elem_2, elem_of_s2);

    int dif = elem_of_s2 - elem_of_s1;
    if (dif != 0) {
        DEBUG_PRINT("\n");
        return dif;
    }

    do {
        --num_of_comp_elem_1;
        --num_of_comp_elem_2;

        elem_of_s1 = prev_letter_sym(p_to_s1->ptr, &num_of_comp_elem_1);
        elem_of_s2 = prev_letter_sym(p_to_s2->ptr, &num_of_comp_elem_2);

        DEBUG_PRINT("element 1 with number %lld: %c\n", num_of_comp_elem_1, elem_of_s1);
        DEBUG_PRINT("element 2 with number %lld: %c\n", num_of_comp_elem_2, elem_of_s2);

        dif = elem_of_s2 - elem_of_s1;

        if (dif != 0) {
            DEBUG_PRINT("\n");
            return dif;
        }

    } while (num_of_comp_elem_1 > 0 && num_of_comp_elem_2 > 0);

    size_t len_dif = p_to_s2->len - p_to_s1->len;

    DEBUG_PRINT("comp result: %lld", len_dif);

    return (int) len_dif;
}

size_t len_of_str(char *str) {
    size_t i = 0;
    for (; str[i] != '\n'; ++i);
    return i + 1;
}

char next_letter_sym(const char str[], size_t* p_to_num_of_sym, size_t len) {
    char sym = str[*p_to_num_of_sym];
    
    while (isalpha(sym) == 0 && *p_to_num_of_sym < len - 1) {
        ++(*p_to_num_of_sym);
        sym = str[*p_to_num_of_sym];
    }

    return(sym);
}

char prev_letter_sym(const char str[], size_t* p_to_num_of_sym) {
    char sym = str[*p_to_num_of_sym];
    
    while (isalpha(sym) == 0 && *p_to_num_of_sym > 0) {
        --(*p_to_num_of_sym);
        sym = str[*p_to_num_of_sym];
    }

    return(sym);
}
