#include <stdio.h>

#pragma once

void merge_sort(void *arr, size_t num_of_elem, size_t el_size, int (*compare) (void *, void *));
void merge_sort_internal(char *array, char* temp, size_t num_of_elem, 
                         size_t el_size, int (*compare) (void *, void *));
void swap_elements(void *p1, void *p2, size_t size_of_element);
int compare_strings_ltor(void *ptr_to_struct1, void *ptr_to_struct2);
int compare_strings_rtol(void *ptr_to_s1, void *ptr_to_s2);
size_t len_of_str(char *str);
char next_letter_sym(const char str[], size_t* p_to_num_of_sym, size_t len);
char prev_letter_sym(const char str[], size_t* p_to_num_of_sym);
