#include "Q1.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Lab8_parse_multiplication_operator(Q8_program_t* program)
{
    const char current = program->source[program->index];
    if (current == '*' || current == '/' || current == '%')
    {
        program->index++;
        return;
    }

    Lab8_invalid_state();
}

void Lab8_parse_additional_operator(Q8_program_t* program)
{
    const char current = program->source[program->index];
    if (current == '+' || current == '-')
    {
        program->index++;
        return;
    }

    Lab8_invalid_state();
}

void Lab8_parse_relational_operator(Q8_program_t* program)
{
    if (program->source[program->index] == '>' || program->source[program->index] == '<')
    {
        program->index++;
        return;
    }

    if (
        (program->source[program->index] == '=' && program->source[program->index + 1] == '=') ||
        (program->source[program->index] == '!' && program->source[program->index + 1] == '=') ||
        (program->source[program->index] == '<' && program->source[program->index + 1] == '=') ||
        (program->source[program->index] == '>' && program->source[program->index + 1] == '=')
    )
    {
        program->index += 2;
        return;
    }

    Lab8_invalid_state();
}

void Lab8_parse_factor(Q8_program_t* program)
{
    if (program->source[program->index] == 'i' && program->source[program->index + 1] == 'd')
    {
        program->index += 2;
        return;
    }

    if (isdigit(program->source[program->index]))
    {
        program->index++;
        return;
    }

    Lab8_invalid_state();
}

void Lab8_parse_term_prime(Q8_program_t* program)
{
    if (program->source[program->index] == '#')
    {
        program->index++;
        return;
    }

    Lab8_parse_multiplication_operator(program);

    if (program->source[program->index] == ' ')
    {
        program->index++;
        Lab8_parse_factor(program);

        if (program->source[program->index] == ' ')
        {
            program->index++;
            Lab8_parse_term_prime(program);
            return;
        }
    }

    Lab8_invalid_state();
}

void Lab8_parse_term(Q8_program_t* program)
{
    Lab8_parse_factor(program);

    if (program->source[program->index] == ' ')
    {
        program->index++;
        Lab8_parse_term_prime(program);
        return;
    }

    Lab8_invalid_state();
}

void Lab8_parse_simple_expression_prime(Q8_program_t* program)
{
    if (program->source[program->index] == '#')
    {
        program->index++;
        return;
    }

    Lab8_parse_additional_operator(program);

    if (program->source[program->index] == ' ')
    {
        program->index++;
        Lab8_parse_term(program);

        if (program->source[program->index] == ' ')
        {
            program->index++;
            Lab8_parse_simple_expression_prime(program);
            return;
        }
    }

    Lab8_invalid_state();
}

void Lab8_parse_simple_expression(Q8_program_t* program)
{
    Lab8_parse_term(program);

    if (program->source[program->index] == ' ')
    {
        program->index++;
        Lab8_parse_simple_expression_prime(program);
        return;
    }

    Lab8_invalid_state();
}

void Lab8_parse_expression_prime(Q8_program_t* program)
{
    if (program->source[program->index] == '#')
    {
        program->index++;
        return;
    }

    Lab8_parse_relational_operator(program);

    if (program->source[program->index] == ' ')
    {
        program->index++;
        Lab8_parse_simple_expression(program);
        return;
    }

    Lab8_invalid_state();
}

void Lab8_parse_expression(Q8_program_t* program)
{
    Lab8_parse_simple_expression(program);

    if (program->source[program->index] == ' ')
    {
        program->index++;
        Lab8_parse_expression_prime(program);
        return;
    }

    Lab8_invalid_state();
}

void Lab8_parse_assign_statement(Q8_program_t* program)
{
    if (
        program->source[program->index] == 'i' &&
        program->source[program->index + 1] == 'd' &&
        program->source[program->index + 2] == ' ' &&
        program->source[program->index + 3] == '=' &&
        program->source[program->index + 4] == ' '
    )
    {
        program->index += 5;
        Lab8_parse_expression(program);
        return;
    }

    Lab8_invalid_state();
}

void Lab8_parse_statement(Q8_program_t* program)
{
    Lab8_parse_assign_statement(program);
}

void Lab8_parse_statement_list(Q8_program_t* program)
{
    if (program->source[program->index] == '#')
    {
        program->index++;
        return;
    }

    Lab8_parse_statement(program);

    if (program->source[program->index] == ' ')
    {
        program->index++;
        Lab8_parse_statement_list(program);
        return;
    }

    if (program->source[program->index] == '}')
        return;

    Lab8_invalid_state();
}

void Lab8_parse_program(Q8_program_t* program)
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
        Lab8_parse_statement_list(program);

        if (program->source[program->index] == '}')
        {
            program->index++;
            return;
        }
    }

    Lab8_invalid_state();
}

void Lab8_valid_state(void)
{
    printf("Valid program.\n");
    exit(EXIT_SUCCESS);
}

void Lab8_invalid_state(void)
{
    printf("Invalid state.\n");
    exit(EXIT_FAILURE);
}

void Lab8_start_parsing(Q8_program_t* program)
{
    Lab8_parse_program(program);

    if (program->index == strlen(program->source) - 1 && program->source[program->index] == '$')
        Lab8_valid_state();
    else
        Lab8_invalid_state();
}
