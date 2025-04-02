#include "Q1.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void Q1_parse_T(Q1_program_t* program);

void Q1_parse_T_prime(Q1_program_t* program);

void Q1_parse_S(Q1_program_t* program)
{
    if (program->source[program->index] == 'a' || program->source[program->index] == '>')
        program->index++;

    else if (program->source[program->index] == '(')
    {
        program->index++;
        Q1_parse_T(program);

        if (program->source[program->index] == ')')
        {
            program->index++;
            return;
        }

        Q1_invalid_state();
    }
}

void Q1_parse_T(Q1_program_t* program)
{
    Q1_parse_S(program);
    Q1_parse_T_prime(program);
}

void Q1_parse_T_prime(Q1_program_t* program)
{
    if (program->source[program->index] == ',')
    {
        program->index++;

        Q1_parse_S(program);
        Q1_parse_T_prime(program);
    }
}

void Q1_valid_state(void)
{
    printf("Valid program.\n");
    exit(EXIT_SUCCESS);
}

void Q1_invalid_state(void)
{
    printf("Invalid program.\n");
    exit(EXIT_FAILURE);
}

void Q1_start_parsing(Q1_program_t* program)
{
    Q1_parse_S(program);

    if (program->index == strlen(program->source) - 1 && program->source[program->index] == '$')
        Q1_valid_state();
    else
        Q1_invalid_state();
}
