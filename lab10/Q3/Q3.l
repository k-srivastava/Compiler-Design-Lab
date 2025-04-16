%{
#include "Q3.tab.h"
#include <string.h>
%}

%%
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return TIMES; }
"/" { return DIVIDE; }
[0-9]+ { yylval.num = atoi(yytext); return NUMBER; }
[ \t\n] {}
. { return yyerror("Unexpected character."); }
%%

int yywrap(void) { return 1; }
