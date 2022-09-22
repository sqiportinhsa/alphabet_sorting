#include <stdio.h>

#pragma once

void bubble_sort(char *pointers[], int amount_of_strings);
void merge_sort(void *arr, size_t num_of_elem, size_t el_size, int (*compare) (void *, void *));
void swap_elements(void *p1, void *p2, size_t size_of_element);
int compare_strings_ltor(void *ptr_to_struct1, void *ptr_to_struct2);
int compare_strings_rtol(void *ptr_to_s1, void *ptr_to_s2);
int len_of_str(char *str);
void copy_arr(void *from, void *to, size_t arr_len, size_t elem_size);
char next_letter_sym(const char str[], int* p_to_num_of_sym, int len);
char prev_letter_sym(const char str[], int* p_to_num_of_sym);
bool is_letter(char sym);
