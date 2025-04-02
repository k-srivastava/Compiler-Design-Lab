#include "Q1.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Lab7_parse_data_type(Q7_program_t* program)
{
    if (
        program->source[program->index] == 'i' &&
        program->source[program->index + 1] == 'n' &&
        program->source[program->index + 2] == 't'
    )
        program->index += 3;

    else if (
        program->source[program->index] == 'c' &&
        program->source[program->index + 1] == 'h' &&
        program->source[program->index + 2] == 'a' &&
        program->source[program->index + 3] == 'r'
    )
        program->index += 4;

    else
        Lab7_invalid_state();
}

void Lab7_parse_identifier_list(Q7_program_t* program)
{
    if (program->source[program->index] == 'i' && program->source[program->index + 1] == 'd')
        program->index += 2;

    else if (
        program->source[program->index] == 'i' &&
        program->source[program->index + 1] == 'd' &&
        program->source[program->index + 2] == ',' &&
        program->source[program->index + 3] == ' '
    )
    {
        program->index += 4;
        Lab7_parse_identifier_list(program);
    }

    else
        Lab7_invalid_state();
}

void Lab7_parse_declarations(Q7_program_t* program)
{
    if (program->source[program->index] == ';')
    {
        program->index++;
        return;
    }

    Lab7_parse_data_type(program);

    if (program->source[program->index] == ' ')
    {
        program->index++;
        Lab7_parse_identifier_list(program);

        if (program->source[program->index] == ';')
        {
            Lab7_parse_declarations(program);
        }

        else
            Lab7_invalid_state();
    }

    else
        Lab7_invalid_state();
}

void Lab7_parse_assign_statement(Q7_program_t* program)
{
    if (
        program->source[program->index] == 'i' &&
        program->source[program->index + 1] == 'd' &&
        program->source[program->index + 2] == ' ' &&
        program->source[program->index + 3] == '=' &&
        program->source[program->index + 4] == ' ' &&
        program->source[program->index + 5] == 'i' &&
        program->source[program->index + 6] == 'd' &&
        program->source[program->index + 7] == ';'
    )
        program->index += 8;

    else if (
        program->source[program->index] == 'i' &&
        program->source[program->index + 1] == 'd' &&
        program->source[program->index + 2] == ' ' &&
        program->source[program->index + 3] == '=' &&
        program->source[program->index + 4] == ' ' &&
        program->source[program->index + 5] == 'n' &&
        program->source[program->index + 6] == 'u' &&
        program->source[program->index + 7] == 'm' &&
        program->source[program->index + 8] == ';'
    )
        program->index += 9;

    else
        Lab7_invalid_state();
}

void Lab7_parse_program(Q7_program_t* program)
{
    if (
        program->source[program->index] == 'm' &&
        program->source[program->index + 1] == 'a' &&
        program->source[program->index + 2] == 'i' &&
        program->source[program->index + 3] == 'n' &&
        program->source[program->index + 4] == '(' &&
        program->source[program->index + 5] == ')' &&
        program->source[program->index + 6] == ' ' &&
        program->source[program->index + 7] == '{'
    )
    {
        program->index += 8;
        Lab7_parse_declarations(program);

        if (program->source[program->index] == ' ')
        {
            program->index++;
            Lab7_parse_assign_statement(program);

            if (program->source[program->index] == '}')
            {
                program->index++;
                return;
            }

            Lab7_invalid_state();
        }

        else
            Lab7_invalid_state();
    }

    else
        Lab7_invalid_state();
}

void Lab7_valid_state(void)
{
    printf("Valid program.\n");
    exit(EXIT_SUCCESS);
}

void Lab7_invalid_state(void)
{
    printf("Invalid state.\n");
    exit(EXIT_FAILURE);
}

void Lab7_start_parsing(Q7_program_t* program)
{
    Lab7_parse_program(program);

    if (program->index == strlen(program->source) - 1 && program->source[program->index] == '$')
        Lab7_valid_state();
    else
        Lab7_invalid_state();
}
