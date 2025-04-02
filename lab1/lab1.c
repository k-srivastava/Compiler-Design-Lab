#include "lab1.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_file(const char* filename, file_t* file)
{
    FILE* file_ptr = fopen(filename, "r");

    if (file_ptr == nullptr)
    {
        fprintf(stderr, "Error opening file: %s.\n", filename);
        return;
    }

    file->name = calloc(strlen(filename), sizeof(char));
    strcpy(file->name, filename);

    fseek(file_ptr, 0, SEEK_END);
    file->size = ftell(file_ptr);
    fseek(file_ptr, 0, SEEK_SET);

    file->contents = calloc(file->size, sizeof(char));
    fread(file->contents, sizeof(char), file->size, file_ptr);

    fclose(file_ptr);
}

void write_file(const file_t* file)
{
    FILE* file_ptr = fopen(file->name, "w");
    if (file_ptr == nullptr)
    {
        fprintf(stderr, "Error opening file: %s.\n", file->name);
        return;
    }

    fwrite(file->contents, sizeof(char), file->size, file_ptr);
    fclose(file_ptr);
}

void free_file(file_t* file)
{
    free(file->name);
    free(file->contents);

    file->name = nullptr;
    file->size = 0;
    file->contents = nullptr;
}

size_t count_lines(const file_t* file)
{
    size_t lines = 0;

    for (size_t i = 0; i < strlen(file->contents); i++)
    {
        if (file->contents[i] == '\n')
            lines++;
    }

    return lines;
}

void reverse_and_write(const char* source_name, file_t* source, const char* destination_name, file_t* destination)
{
    read_file(source_name, source);

    destination->name = (char*)destination_name;
    destination->size = source->size;
    destination->contents = calloc(destination->size, sizeof(char));

    for (size_t i = 0; i < source->size; i++)
        destination->contents[destination->size - i - 1] = source->contents[i];

    write_file(destination);
}

void merge_alternatively(
    const char* source_name_1, file_t* source_1, const char* source_name_2, file_t* source_2,
    const char* destination_name, file_t* destination
)
{
    read_file(source_name_1, source_1);
    read_file(source_name_2, source_2);

    destination->name = (char*)destination_name;
    destination->size = source_1->size + source_2->size;
    destination->contents = calloc(destination->size, sizeof(char));

    bool first_file = true;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;


    while (k < destination->size)
    {
        if (first_file)
        {
            while (source_1->contents[i] != '\n' || source_1->contents[i] != '\0')
                destination->contents[k++] = source_1->contents[i++];

            first_file = false;
        }

        else
        {
            while (source_2->contents[j] != '\n' || source_2->contents[j] != '\0')
                destination->contents[k++] = source_2->contents[j++];

            first_file = true;
        }
    }

    printf("%s\n", destination->contents);
}
