%{
#include <stdio.h>
#include <stdlib.h>
%}

%union {
    char *str;
    int num;
}

%token IF ELSE SWITCH CASE COLON SEMICOLON LPAREN RPAREN LBRACE RBRACE
%token <str> IDENTIFIER
%token <num> NUMBER

%%
program:
    statement_list
    ;

statement_list:
    statement
    | statement_list statement
    ;

statement:
    if_statement
    | switch_statement
    | IDENTIFIER SEMICOLON
    | NUMBER SEMICOLON
    ;

if_statement:
    IF LPAREN condition RPAREN statement ELSE statement {
        printf("Valid if-else statement.\n");
    }
    | IF LPAREN condition RPAREN statement {
        printf("Valid if statement.\n");
    }
    ;

switch_statement:
    SWITCH LPAREN condition RPAREN LBRACE case_list RBRACE {
        printf("Valid switch-statement.\n");
    }
    ;

case_list:
    case_clause
    | case_list case_clause
    ;

case_clause:
    CASE NUMBER COLON statement
    ;

condition:
    IDENTIFIER
    | NUMBER
    ;
%%

int main(void)
{
    printf("Enter a decision-making statement: ");
    yyparse();
    return 0;
}

void yyerror(const char* s)
{
    fprintf(stderr, "Error: %s\n", s);
}
