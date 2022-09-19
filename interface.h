#include <stdio.h>

int get_file_names(int argc, const char *argv[], char input_file[], char output_file[]);
void write_text(FILE *output, char *text[], int amount_of_strings);
size_t elements_in_file(char file_name[]);