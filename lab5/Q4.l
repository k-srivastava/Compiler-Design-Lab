%{
    int num_printfs = 0;
    int num_scanfs = 0;
%}

%%
"printf" { fprintf(yyout, "WRITE"); num_printfs++; }
"scanf" { fprintf(yyout, "READ"); num_scanfs++; }
%%

int main(void)
{
    yylex();

    printf("Printfs: %d\n", num_printfs);
    printf("Scanfs: %d\n", num_scanfs);

    return 0;
}

int yywrap() { return 1; }
