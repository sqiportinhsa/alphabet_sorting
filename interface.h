#include <stdio.h>

int get_file_names(int argc, const char *argv[], char input_file[], char output_file[]);
void write_text(FILE *output, char *text[], int amount_of_strings);
size_t elements_in_file(char file_name[]);
size_t read_text(char text[], size_t amount_of_symbols, FILE *input);
int count_strings(char text[], size_t amount_of_symbols);
void place_pointers(struct String strings[], char *text, size_t amount_of_symbols, 
                                                            int amount_of_strings);