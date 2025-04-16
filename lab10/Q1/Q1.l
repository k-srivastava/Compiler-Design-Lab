%{
#include "Q1.tab.h"
#include <string.h>
%}

%%
int       { return INT; }
float     { return FLOAT; }
char      { return CHAR; }
[A-Za-z_][A-Za-z0-9_]* { yylval.str = strdup(yytext); return IDENTIFIER; }
";"       { return SEMICOLON; }
[ \t\n]   {}
.         { yyerror("Unknown character."); }
%%
