%{
    int vowels = 0;
    int consonants = 0;
%}

%%
[aeiouAEIOU] { vowels++; }
[a-zA-Z] { consonants++; }
%%

int main(void)
{
    printf("Enter a word: ");

    yylex();

    printf("Vowels: %d, Consonants: %d\n", vowels, consonants);
    return 0;
}

int yywrap() { return 1; }
