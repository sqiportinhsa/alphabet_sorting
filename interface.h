#include <stdio.h>

#pragma once

int get_file_names(int argc, const char *argv[], char input_file[], char output_file[]);
size_t read_text(char text[], size_t amount_of_symbols, FILE *input);
int count_strings(char text[], size_t amount_of_symbols);
void place_pointers(struct String strings[], char *text, size_t amount_of_symbols, 
                                                            int amount_of_strings);
void write_text_by_strings(FILE *output, struct String strings[], int amount_of_strings);
void write_text_by_chars(FILE *output, char text[], size_t amount_of_symbols);
size_t elements_in_file(char file_name[]);
void print_string(char *string);
void print_strings(struct String *str, size_t amount_of_strings);
