#include "Q1.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Lab9_parse_assign_statement(Q9_program_t* program)
{
    if (
        program->source[program->index] == 'l' &&
        program->source[program->index + 1] == 'e' &&
        program->source[program->index + 2] == 't'
    )
        program->index += 3;

    else if (
        program->source[program->index] == 'v' &&
        program->source[program->index + 1] == 'a' &&
        program->source[program->index + 2] == 'r'
    )
        program->index += 3;

    else
    {
        printf(
            "Expected 'let' or 'var'. Got: %c%c%c.\n", program->source[program->index],
            program->source[program->index + 1], program->source[program->index + 2]
        );
        exit(EXIT_FAILURE);
    }
}

void Lab9_parse_expression(Q9_program_t* program)
{
    if (
        program->source[program->index] == 'e' &&
        program->source[program->index + 1] == 'x' &&
        program->source[program->index + 2] == 'p' &&
        program->source[program->index + 3] == 'r'
    )
        program->index += 4;

    else
    {
        printf("Expected 'expr'. Got: %c.\n", program->source[program->index]);
        exit(EXIT_FAILURE);
    }
}

void Lab9_parse_statement_list(Q9_program_t* program)
{
    if (
        program->source[program->index] == 's' &&
        program->source[program->index + 1] == 't' &&
        program->source[program->index + 2] == 'm' &&
        program->source[program->index + 3] == 't'
    )
        program->index += 4;

    else
    {
        printf("Expected 'stmt'. Got: %c.\n", program->source[program->index]);
        exit(EXIT_FAILURE);
    }
}

void Lab9_parse_d_prime(Q9_program_t* program)
{
    if (
        program->source[program->index] == ' ' &&
        program->source[program->index + 1] == 'e' &&
        program->source[program->index + 2] == 'l' &&
        program->source[program->index + 3] == 's' &&
        program->source[program->index + 4] == 'e'
    )
    {
        program->index += 5;

        if (program->source[program->index] == ' ' && program->source[program->index + 1] == '{')
        {
            program->index += 2;
            Lab9_parse_statement_list(program);

            if (program->source[program->index] == '}')
                program->index++;

            else
            {
                printf("Expected '}'. Got: %c.\n", program->source[program->index]);
                exit(EXIT_FAILURE);
            }
        }

        else
        {
            printf("Expected ' {'. Got: %c%c.\n", program->source[program->index], program->source[program->index + 1]);
            exit(EXIT_FAILURE);
        }
    }
}

void Lab9_parse_decision_statement(Q9_program_t* program)
{
    Lab9_parse_expression(program);

    if (
        program->source[program->index] == ')' &&
        program->source[program->index + 1] == ' ' &&
        program->source[program->index + 2] == '{'
    )
    {
        program->index += 3;
        Lab9_parse_statement_list(program);

        if (program->source[program->index] == '}')
        {
            program->index++;
            Lab9_parse_d_prime(program);
        }

        else
        {
            printf("Expected '}'. Got: %c.\n", program->source[program->index]);
            exit(EXIT_FAILURE);
        }
    }

    else
    {
        printf(
            "Expected ') {'. Got: %c%c%c.\n", program->source[program->index], program->source[program->index + 1],
            program->source[program->index + 2]
        );
        exit(EXIT_FAILURE);
    }
}

void Lab9_parse_while_statement(Q9_program_t* program)
{
    Lab9_parse_expression(program);

    if (
        program->source[program->index] == ')' &&
        program->source[program->index + 1] == ' ' &&
        program->source[program->index + 2] == '{'
    )
    {
        program->index += 3;
        Lab9_parse_statement_list(program);

        if (program->source[program->index] == '}')
            program->index++;

        else
        {
            printf("Expected '}'. Got: %c.\n", program->source[program->index]);
            exit(EXIT_FAILURE);
        }
    }

    else
    {
        printf(
            "Expected ') {'. Got: %c%c%c.\n", program->source[program->index], program->source[program->index + 1],
            program->source[program->index + 2]
        );
        exit(EXIT_FAILURE);
    }
}

void Lab9_parse_for_statement(Q9_program_t* program)
{
    Lab9_parse_assign_statement(program);

    if (program->source[program->index] == ';' && program->source[program->index + 1] == ' ')
    {
        program->index += 2;
        Lab9_parse_expression(program);

        if (program->source[program->index] == ';' && program->source[program->index + 1] == ' ')
        {
            program->index += 2;
            Lab9_parse_assign_statement(program);

            if (
                program->source[program->index] == ')' &&
                program->source[program->index + 1] == ' ' &&
                program->source[program->index + 2] == '{'
            )
            {
                program->index += 3;
                Lab9_parse_statement_list(program);

                if (program->source[program->index] == '}')
                    program->index++;

                else
                {
                    printf("Expected '}'. Got: %c.\n", program->source[program->index]);
                    exit(EXIT_FAILURE);
                }
            }

            else
            {
                printf(
                    "Expected ') {'. Got: %c%c%c.\n", program->source[program->index], program->source[program->index + 1],
                    program->source[program->index + 2]
                );
                exit(EXIT_FAILURE);
            }
        }

        else
        {
            printf("Expected '; '. Got: %c%c.\n", program->source[program->index], program->source[program->index + 1]);
            exit(EXIT_FAILURE);
        }
    }

    else
    {
        printf("Expected '; '. Got: %c%c.\n", program->source[program->index], program->source[program->index + 1]);
        exit(EXIT_FAILURE);
    }
}

void Lab9_parse_program(Q9_program_t* program)
{
    if (
        program->source[program->index] == 'i' &&
        program->source[program->index + 1] == 'f' &&
        program->source[program->index + 2] == ' ' &&
        program->source[program->index + 3] == '('
    )
    {
        program->index += 4;
        Lab9_parse_decision_statement(program);
    }

    else if (
        program->source[program->index] == 'w' &&
        program->source[program->index + 1] == 'h' &&
        program->source[program->index + 2] == 'i' &&
        program->source[program->index + 3] == 'l' &&
        program->source[program->index + 4] == 'e' &&
        program->source[program->index + 5] == ' ' &&
        program->source[program->index + 6] == '('
    )
    {
        program->index += 7;
        Lab9_parse_while_statement(program);
    }

    else if (
        program->source[program->index] == 'f' &&
        program->source[program->index + 1] == 'o' &&
        program->source[program->index + 2] == 'r' &&
        program->source[program->index + 3] == ' ' &&
        program->source[program->index + 4] == '('
    )
    {
        program->index += 5;
        Lab9_parse_for_statement(program);
    }

    else
    {
        printf("Expected if, while, or for statement. Got: %c.\n", program->source[program->index]);
        exit(EXIT_FAILURE);
    }
}

void Lab9_valid_state(void)
{
    printf("Valid program.\n");
    exit(EXIT_SUCCESS);
}

void Lab9_invalid_state(void)
{
    printf("Invalid state.\n");
    exit(EXIT_FAILURE);
}

void Lab9_start_parsing(Q9_program_t* program)
{
    Lab9_parse_program(program);

    if (program->index == strlen(program->source) - 1 && program->source[program->index] == '$')
        Lab9_valid_state();
    else
        Lab9_invalid_state();
}
