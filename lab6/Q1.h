#ifndef Q1_H
#define Q1_H

#include <stddef.h>

typedef struct Q1_program_s
{
    char* source;
    size_t index;
} Q1_program_t;

void Q1_valid_state(void);

void Q1_invalid_state(void);

void Q1_start_parsing(Q1_program_t* program);

#endif //Q1_H
