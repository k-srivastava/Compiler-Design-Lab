#ifndef Q2_H
#define Q2_H

#include <stddef.h>

typedef struct Q2_program_s
{
    char* source;
    size_t index;
} Q2_program_t;

void Q2_valid_state(void);

void Q2_invalid_state(void);

void Q2_start_parsing(Q2_program_t* program);

#endif //Q2_H
