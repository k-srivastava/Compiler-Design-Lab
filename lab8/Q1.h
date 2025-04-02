#ifndef Q1_H
#define Q1_H

#include <stddef.h>

typedef struct Q8_program_s
{
    char* source;
    size_t index;
} Q8_program_t;

void Lab8_valid_state(void);

void Lab8_invalid_state(void);

void Lab8_start_parsing(Q8_program_t* program);

#endif
