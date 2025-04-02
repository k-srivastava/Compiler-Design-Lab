%{
    int positive_ints = 0;
    int negative_ints = 0;

    int positive_floats = 0;
    int negative_floats = 0;
%}

%%
[0-9]+.[0-9]+  { positive_floats++; }
-[0-9]+.[0-9]+ { negative_floats++; }
[0-9]+         { positive_ints++; }
-[0-9]+        { negative_ints++; }
%%

int main(void)
{
    yylex();

    printf("Positive Ints: %d\n", positive_ints);
    printf("Negative Ints: %d\n", negative_ints);

    printf("\nPositive Floats: %d\n", positive_floats);
    printf("Negative Floats: %d\n", negative_floats);

    return 0;
}

int yywrap() { return 1; }
