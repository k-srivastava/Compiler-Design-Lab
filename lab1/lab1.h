#ifndef LAB1_H
#define LAB1_H

#include <stddef.h>

typedef struct file_s
{
    char* name;
    size_t size;
    char* contents;
} file_t;

void read_file(const char* filename, file_t* file);

void write_file(const file_t* file);

void free_file(file_t* file);

size_t count_lines(const file_t* file);

void reverse_and_write(const char* source_name, file_t* source, const char* destination_name, file_t* destination);

void merge_alternatively(
    const char* source_name_1, file_t* source_1, const char* source_name_2, file_t* source_2,
    const char* destination_name, file_t* destination
);

#endif //LAB1_H
