#include "sorting.h"

#include <string.h>

void bubble_sort(char *pointers[], int amount_of_strings) {
    int n_sorting_pointer = 1;
    int n_of_sortings = 1;
    
    for (; n_of_sortings < amount_of_strings; ++n_of_sortings) {
        n_sorting_pointer = 1;

        for (; n_sorting_pointer < amount_of_strings; ++n_sorting_pointer) {

            if (!strings_are_in_correct_order(pointers[n_sorting_pointer - 1], 
                                              pointers[n_sorting_pointer    ])) {               
                swap_pointers(pointers[n_sorting_pointer - 1], 
                              pointers[n_sorting_pointer    ]);
            }
        }
    }
}

void swap_pointers(char *p1, char *p2) {
    char *temp = p1;
    p1 = p2;
    p2 = temp;
}

bool strings_are_in_correct_order(char *p_to_s1, char *p_to_s2) {
    size_t len1 = strlen(p_to_s1) - 1;
    size_t len2 = strlen(p_to_s2) - 1;
    size_t num_of_comp_elem = 0;

    while (num_of_comp_elem < len1 && num_of_comp_elem < len2) {
        char elem_of_s1 = p_to_s1[num_of_comp_elem];
        char elem_of_s2 = p_to_s2[num_of_comp_elem];

        if (elem_of_s1 > elem_of_s2) {
            return false;
        }
        
        if (elem_of_s1 < elem_of_s2) {
            return true;
        }

        ++num_of_comp_elem;
    }

    if (len2 < len1) {
        return false;
    }

    return true;
}