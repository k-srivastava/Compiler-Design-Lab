%{
#include <stdio.h>
#include <stdlib.h>
%}

%union{
    int num;
}

%token <num> NUMBER
%token PLUS MINUS TIMES DIVIDE

%type <num> expression

%left PLUS MINUS
%left TIMES DIVIDE

%%
program:
    statement_list
    ;

statement_list:
    statement
    | statement_list statement
    ;

statement:
    '\n'
    | expression '\n' { printf("Result: %d\n", $1); }
    ;

expression:
    NUMBER { $$ = $1; }
    | expression expression PLUS {
        $$ = $1 + $2;
        printf("%d\n", $$);
    }
    | expression expression MINUS { $$ = $1 - $2; }
    | expression expression TIMES { $$ = $1 * $2; }
    | expression expression DIVIDE { $$ = $1 / $2; }
    ;
%%

int main(void)
{
    printf("Enter a postfix expression:\n");
    yyparse();
    return 0;
}

void yyerror(const char* s)
{
    fprintf(stderr, "Error: %s\n", s);
}
