#include "Q3.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Q3_parse_A(Q3_program_t* program);

void Q3_parse_A_prime(Q3_program_t* program);

void Q3_parse_B(Q3_program_t* program);

void Q3_parse_S(Q3_program_t* program)
{
    if (program->source[program->index] == 'a')
    {
        program->index++;
        Q3_parse_A(program);

        if (program->source[program->index] == 'c')
        {
            program->index++;
            Q3_parse_B(program);

            if (program->source[program->index] == 'e')
                program->index++;

            else
                Q3_invalid_state();
        }

        else
            Q3_invalid_state();
    }
}

void Q3_parse_A(Q3_program_t* program)
{
    if (program->source[program->index] == 'b')
    {
        program->index++;
        Q3_parse_A_prime(program);
    }
}

void Q3_parse_A_prime(Q3_program_t* program)
{
    if (program->source[program->index] == 'b')
    {
        program->index++;
        Q3_parse_A(program);
    }
}

void Q3_parse_B(Q3_program_t* program)
{
    if (program->source[program->index] == 'd')
        program->index++;
}

void Q3_valid_state(void)
{
    printf("Valid program.\n");
    exit(EXIT_SUCCESS);
}

void Q3_invalid_state(void)
{
    printf("Invalid program.\n");
    exit(EXIT_FAILURE);
}

void Q3_start_parsing(Q3_program_t* program)
{
    Q3_parse_S(program);

    if (program->index == strlen(program->source) - 1 && program->source[program->index] == '$')
        Q3_valid_state();
    else
        Q3_invalid_state();
}
