#include <stdio.h>

void bubble_sort(char *pointers[], int amount_of_strings);
void merge_sort(char *arr[], size_t num_of_elem, size_t el_size, 
                int (*compare) (char *, char *));
void swap_pointers(char *p1, char *p2);
int compare_strings(char *p_to_s1, char *p_to_s2);
int len_of_str(char *str);
void print_string(char *string);
void copy_arr(char* arr[], char* copy_of_arr[], size_t arr_len);
void place_pointers(char text[], char *pointers_to_strings[], size_t amount_of_symbols);
void print_array(char *arr[], size_t num_of_elem);