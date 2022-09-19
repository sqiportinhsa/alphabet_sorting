#include <stdio.h>

void bubble_sort(char *pointers[], int amount_of_strings);
void merge_sort(void *arr[], size_t num_of_elem, size_t el_size, 
                int (*compare) (void *, void *));
void swap_pointers(char **p1, char **p2);
int compare_strings(void *p_to_s1, void *p_to_s2);
int reversed_comparator(void *ptr_to_s1, void *ptr_to_s2);
int len_of_str(char *str);
void print_string(char *string);
void copy_arr(char* arr[], char* copy_of_arr[], size_t arr_len);
void print_array(char *arr[], size_t num_of_elem);
char next_letter_sym(const char str[], int* p_to_num_of_sym, int len);
char prev_letter_sym(const char str[], int* p_to_num_of_sym);
bool is_letter(char sym);