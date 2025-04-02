#ifndef Q1_H
#define Q1_H

#include <stddef.h>

typedef struct Q7_program_s
{
    char* source;
    size_t index;
} Q7_program_t;

void Lab7_valid_state(void);

void Lab7_invalid_state(void);

void Lab7_start_parsing(Q7_program_t* program);

#endif
