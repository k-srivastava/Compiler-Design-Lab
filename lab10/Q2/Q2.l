%{
#include "Q2.tab.h"
#include <string.h>
%}

%%
if      { return IF; }
else    { return ELSE; }
switch  { return SWITCH; }
case    { return CASE; }
[A-Za-z_][A-Za-z0-9_]* { yylval.str = strdup(yytext); return IDENTIFIER; }
[0-9]+  { yylval.num = atoi(yytext); return NUMBER; }

"("     { return LPAREN; }
")"     { return RPAREN; }
"{"     { return LBRACE; }
"}"     { return RBRACE; }
":"     { return COLON; }
";"     { return SEMICOLON; }
[ \t\n] {}
.       { yyerror("Unknown character."); }
%%
