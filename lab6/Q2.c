#include "Q2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Q2_parse_U(Q2_program_t* program);

void Q2_parse_V(Q2_program_t* program);

void Q2_parse_W(Q2_program_t* program);

void Q2_parse_S(Q2_program_t* program)
{
    Q2_parse_U(program);
    Q2_parse_V(program);
    Q2_parse_W(program);
}

void Q2_parse_U(Q2_program_t* program)
{
    if (program->source[program->index] == '(')
    {
        program->index++;
        Q2_parse_S(program);

        if (program->source[program->index] == ')')
        {
            program->index++;
            return;
        }

        Q2_invalid_state();
    }

    else if (program->source[program->index] == 'a')
    {
        program->index++;
        Q2_parse_S(program);

        if (program->source[program->index] == 'b')
        {
            program->index++;
            return;
        }

        Q2_invalid_state();
    }

    else if (program->source[program->index] == 'd')
        program->index++;
}

void Q2_parse_V(Q2_program_t* program)
{
    if (program->source[program->index] == 'a')
    {
        program->index++;
        Q2_parse_V(program);
    }
}

void Q2_parse_W(Q2_program_t* program)
{
    if (program->source[program->index] == 'c')
    {
        program->index++;
        Q2_parse_W(program);
    }
}

void Q2_valid_state(void)
{
    printf("Valid program.\n");
    exit(EXIT_SUCCESS);
}

void Q2_invalid_state(void)
{
    printf("Invalid program.\n");
    exit(EXIT_FAILURE);
}

void Q2_start_parsing(Q2_program_t* program)
{
    Q2_parse_S(program);

    if (program->index == strlen(program->source) - 1 && program->source[program->index] == '$')
        Q2_valid_state();
    else
        Q2_invalid_state();
}
