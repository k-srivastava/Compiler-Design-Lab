#ifndef Q1_H
#define Q1_H

#include <stddef.h>

typedef struct Q9_program_s
{
    char* source;
    size_t index;
} Q9_program_t;

void Lab9_valid_state(void);

void Lab9_invalid_state(void);

void Lab9_start_parsing(Q9_program_t* program);


#endif
