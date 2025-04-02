#ifndef LAB3_H
#define LAB3_H

#include <stdio.h>

#define MAX_TOKENS 1024

typedef enum token_type_e
{
    TT_LEFT_PARENTHESIS, TT_RIGHT_PARENTHESIS, TT_LEFT_BRACE, TT_RIGHT_BRACE, TT_LEFT_BRACKET, TT_RIGHT_BRACKET,

    TT_COMMA, TT_DOT, TT_SEMICOLON, TT_HASH,

    TT_PLUS, TT_PLUS_PLUS, TT_PLUS_EQUALS,
    TT_MINUS, TT_MINUS_MINUS, TT_MINUS_EQUALS,
    TT_ASTERISK, TT_ASTERISK_EQUALS,
    TT_SLASH, TT_SLASH_EQUALS,
    TT_PERCENT, TT_PERCENT_EQUALS,
    TT_AND, TT_AND_EQUALS,
    TT_OR, TT_OR_EQUALS,
    TT_XOR, TT_XOR_EQUALS,
    TT_LESSER_THAN, TT_LESSER_THAN_EQUALS,
    TT_GREATER_THAN, TT_GREATER_THAN_EQUALS,
    TT_ASSIGN, TT_EQUALS,
    TT_NOT, TT_NOT_EQUALS,

    TT_IDENTIFIER, TT_STRING, TT_NUMBER,
    TT_CONST, TT_INT, TT_FLOAT, TT_DOUBLE, TT_CHAR, TT_VOID, TT_TYPEDEF, TT_ENUM, TT_STRUCT,

    TT_DO, TT_ELSE, TT_FOR, TT_IF, TT_RETURN, TT_WHILE,

    TT_EOF
} token_type_t;

typedef struct token_s
{
    token_type_t type;
    char* lexeme;
    void* literal;
    size_t line;
} token_t;

typedef struct lexer_s
{
    char* source;
    size_t start;
    size_t current;
    size_t line;

    token_t tokens[MAX_TOKENS];
    size_t token_count;
} lexer_t;

char* get_token_type_string(token_type_t token_type);

token_t init_token(token_type_t type, char* lexeme, void* literal, size_t line);

void display_token(FILE* stream, const token_t* token);

void scan_tokens(lexer_t* lexer);

#endif //LAB3_H
