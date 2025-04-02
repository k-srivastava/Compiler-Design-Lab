%{
    int words = 0;
    int characters = 0;
    int blanks = 0;
    int lines = 0;
    int in_word = 0;
%}

%%
[a-zA-Z]+ {
    if (!in_word) {
        words++; 
        in_word = 1; 
    }

    characters += strlen(yytext); 
}

[ ] { 
    blanks++; 
    in_word = 0; 
}

\n { 
    lines++; 
    in_word = 0; 
}
%%

int main(void)
{
    yylex();

    printf("Words: %d | Characters: %d | Blanks: %d | Lines: %d\n", words, characters, blanks, lines);
    return 0;
}

int yywrap() { return 1; }
