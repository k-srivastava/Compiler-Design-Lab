%{
#include <stdio.h>
#include <stdlib.h>
%}

%union {
    char *str;
}

%token INT FLOAT CHAR SEMICOLON
%token <str> IDENTIFIER

%%
declaration:
    type IDENTIFIER SEMICOLON {
        printf("Valid Declaration: %s\n", $2);
        free($2);
    }
    ;

type:
    INT     { printf("Type: int\n"); }
    | FLOAT { printf("Type: float\n"); }
    | CHAR  { printf("Type: char\n"); }
    ;
%%

int main(void)
{
    printf("Enter a declaration statement: ");
    yyparse();
    return 0;
}

void yyerror(const char *s)
{
    fprintf(stderr, "Error: %s\n", s);
}
