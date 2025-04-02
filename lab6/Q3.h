#ifndef Q3_H
#define Q3_H

#include <stddef.h>

typedef struct Q3_program_s
{
    char* source;
    size_t index;
} Q3_program_t;

void Q3_valid_state(void);

void Q3_invalid_state(void);

void Q3_start_parsing(Q3_program_t* program);

#endif //Q3_H
