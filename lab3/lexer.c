#include "lexer.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

token_type_t get_token_type_or_identifier(const char* substring)
{
    if (strcmp(substring, "const") == 0)
        return TT_CONST;

    if (strcmp(substring, "int") == 0)
        return TT_INT;

    if (strcmp(substring, "float") == 0)
        return TT_FLOAT;

    if (strcmp(substring, "double") == 0)
        return TT_DOUBLE;

    if (strcmp(substring, "char") == 0)
        return TT_CHAR;

    if (strcmp(substring, "void") == 0)
        return TT_VOID;

    if (strcmp(substring, "typedef") == 0)
        return TT_TYPEDEF;

    if (strcmp(substring, "enum") == 0)
        return TT_ENUM;

    if (strcmp(substring, "struct") == 0)
        return TT_STRUCT;

    if (strcmp(substring, "do") == 0)
        return TT_DO;

    if (strcmp(substring, "else") == 0)
        return TT_ELSE;

    if (strcmp(substring, "for") == 0)
        return TT_FOR;

    if (strcmp(substring, "if") == 0)
        return TT_IF;

    if (strcmp(substring, "return") == 0)
        return TT_RETURN;

    if (strcmp(substring, "while") == 0)
        return TT_WHILE;

    return TT_IDENTIFIER;
}

char* get_token_type_string(const token_type_t token_type)
{
    switch (token_type)
    {
        case TT_LEFT_PARENTHESIS:
            return "TT_LEFT_PARENTHESIS";

        case TT_RIGHT_PARENTHESIS:
            return "TT_RIGHT_PARENTHESIS";

        case TT_LEFT_BRACE:
            return "TT_LEFT_BRACE";

        case TT_RIGHT_BRACE:
            return "TT_RIGHT_BRACE";

        case TT_LEFT_BRACKET:
            return "TT_LEFT_BRACKET";

        case TT_RIGHT_BRACKET:
            return "TT_RIGHT_BRACKET";

        case TT_COMMA:
            return "TT_COMMA";

        case TT_DOT:
            return "TT_DOT";

        case TT_SEMICOLON:
            return "TT_SEMICOLON";

        case TT_HASH:
            return "TT_HASH";

        case TT_PLUS:
            return "TT_PLUS";

        case TT_PLUS_PLUS:
            return "TT_PLUS_PLUS";

        case TT_PLUS_EQUALS:
            return "TT_PLUS_EQUALS";

        case TT_MINUS:
            return "TT_MINUS";

        case TT_MINUS_MINUS:
            return "TT_MINUS_MINUS";

        case TT_MINUS_EQUALS:
            return "TT_MINUS_EQUALS";

        case TT_ASTERISK:
            return "TT_ASTERISK";

        case TT_ASTERISK_EQUALS:
            return "TT_ASTERISK_EQUALS";

        case TT_SLASH:
            return "TT_SLASH";

        case TT_SLASH_EQUALS:
            return "TT_SLASH_EQUALS";

        case TT_PERCENT:
            return "TT_PERCENT";

        case TT_PERCENT_EQUALS:
            return "TT_PERCENT_EQUALS";

        case TT_AND:
            return "TT_AND";

        case TT_AND_EQUALS:
            return "TT_AND_EQUALS";

        case TT_OR:
            return "TT_OR";

        case TT_OR_EQUALS:
            return "TT_OR_EQUALS";

        case TT_XOR:
            return "TT_XOR";

        case TT_XOR_EQUALS:
            return "TT_XOR_EQUALS";

        case TT_LESSER_THAN:
            return "TT_LESSER_THAN";

        case TT_LESSER_THAN_EQUALS:
            return "TT_LESSER_THAN_EQUALS";

        case TT_GREATER_THAN:
            return "TT_GREATER_THAN";

        case TT_GREATER_THAN_EQUALS:
            return "TT_GREATER_THAN_EQUALS";

        case TT_ASSIGN:
            return "TT_ASSIGN";

        case TT_EQUALS:
            return "TT_EQUALS";

        case TT_NOT:
            return "TT_NOT";

        case TT_NOT_EQUALS:
            return "TT_NOT_EQUALS";

        case TT_IDENTIFIER:
            return "TT_IDENTIFIER";

        case TT_STRING:
            return "TT_STRING";

        case TT_NUMBER:
            return "TT_NUMBER";

        case TT_CONST:
            return "TT_CONST";

        case TT_INT:
            return "TT_INT";

        case TT_FLOAT:
            return "TT_FLOAT";

        case TT_DOUBLE:
            return "TT_DOUBLE";

        case TT_CHAR:
            return "TT_CHAR";

        case TT_VOID:
            return "TT_VOID";

        case TT_TYPEDEF:
            return "TT_TYPEDEF";

        case TT_ENUM:
            return "TT_ENUM";

        case TT_STRUCT:
            return "TT_STRUCT";

        case TT_DO:
            return "TT_DO";

        case TT_ELSE:
            return "TT_ELSE";

        case TT_FOR:
            return "TT_FOR";

        case TT_IF:
            return "TT_IF";

        case TT_RETURN:
            return "TT_RETURN";

        case TT_WHILE:
            return "TT_WHILE";

        case TT_EOF:
            return "TT_EOF";

        default:
            return "UNKNOWN_TOKEN";
    }
}

token_t init_token(const token_type_t type, char* lexeme, void* literal, const size_t line)
{
    token_t token;

    token.type = type;
    token.lexeme = lexeme;
    token.literal = literal;
    token.line = line;

    return token;
}

void display_token(FILE* stream, const token_t* token)
{
    fprintf(stream, "Type: %s | Lexeme: %s\n", get_token_type_string(token->type), token->lexeme);
}

void add_token(lexer_t* lexer, const token_type_t type, void* literal)
{
    char substring[lexer->current - lexer->start];
    strncpy(substring, lexer->source + lexer->start, lexer->current - lexer->start);

    const auto token = init_token(type, substring, literal, lexer->line);
    lexer->tokens[lexer->token_count++] = token;
}

bool is_at_end(const lexer_t* lexer)
{
    return lexer->current >= strlen(lexer->source);
}

char advance(lexer_t* lexer)
{
    return lexer->source[lexer->current++];
}

char peek(const lexer_t* lexer)
{
    if (is_at_end(lexer))
        return '\0';
    return lexer->source[lexer->current];
}

char peek_next(const lexer_t* lexer)
{
    if (lexer->current + 1 >= strlen(lexer->source))
        return '\0';
    return lexer->source[lexer->current + 1];
}

bool match(lexer_t* lexer, const char expected)
{
    if (is_at_end(lexer))
        return false;

    if (lexer->source[lexer->current] != expected)
        return false;

    lexer->current++;
    return true;
}

void scan_number(lexer_t* lexer)
{
    while (isdigit(peek(lexer)))
        advance(lexer);

    if (peek(lexer) == '.' && isdigit(peek_next(lexer)))
    {
        advance(lexer);
        while (isdigit(peek(lexer)))
            advance(lexer);
    }

    char substring[lexer->current - lexer->start];
    strncpy(substring, lexer->source + lexer->start, lexer->current - lexer->start);

    float value = strtof(substring, nullptr);
    add_token(lexer, TT_NUMBER, &value);
}

void scan_identifier(lexer_t* lexer)
{
    while (isalnum(peek(lexer)))
        advance(lexer);

    char substring[lexer->current - lexer->start];
    strncpy(substring, lexer->source + lexer->start, lexer->current - lexer->start);

    const token_type_t type = get_token_type_or_identifier(substring);
    add_token(lexer, type, nullptr);
}

void scan_token(lexer_t* lexer)
{
    const char character = advance(lexer);

    switch (character)
    {
        case '(':
            add_token(lexer, TT_LEFT_PARENTHESIS, nullptr);
            break;

        case ')':
            add_token(lexer, TT_RIGHT_PARENTHESIS, nullptr);
            break;

        case '{':
            add_token(lexer, TT_LEFT_BRACE, nullptr);
            break;

        case '}':
            add_token(lexer, TT_RIGHT_BRACE, nullptr);
            break;

        case '[':
            add_token(lexer, TT_LEFT_BRACKET, nullptr);
            break;

        case ']':
            add_token(lexer, TT_RIGHT_BRACKET, nullptr);
            break;

        case ',':
            add_token(lexer, TT_COMMA, nullptr);
            break;

        case '.':
            add_token(lexer, TT_DOT, nullptr);
            break;

        case ';':
            add_token(lexer, TT_SEMICOLON, nullptr);
            break;

        case '#':
            add_token(lexer, TT_HASH, nullptr);
            break;

        case '+':
        {
            if (match(lexer, '+'))
                add_token(lexer, TT_PLUS_PLUS, nullptr);
            else if (match(lexer, '='))
                add_token(lexer, TT_PLUS_EQUALS, nullptr);
            else
                add_token(lexer, TT_PLUS, nullptr);

            break;
        }

        case '-':
        {
            if (match(lexer, '-'))
                add_token(lexer, TT_MINUS_MINUS, nullptr);
            else if (match(lexer, '='))
                add_token(lexer, TT_MINUS_EQUALS, nullptr);
            else
                add_token(lexer, TT_MINUS, nullptr);

            break;
        }

        case '*':
            add_token(lexer, match(lexer, '=') ? TT_ASTERISK_EQUALS : TT_ASTERISK, nullptr);
            break;

        case '/':
        {
            if (match(lexer, '/'))
            {
                while (peek(lexer) != '\n' && !is_at_end(lexer))
                    advance(lexer);
            }

            else if (match(lexer, '='))
                add_token(lexer, TT_SLASH_EQUALS, nullptr);

            else
                add_token(lexer, TT_SLASH, nullptr);

            break;
        }

        case '%':
            add_token(lexer, match(lexer, '=') ? TT_PERCENT_EQUALS : TT_PERCENT, nullptr);
            break;

        case '&':
            add_token(lexer, match(lexer, '=') ? TT_AND_EQUALS : TT_AND, nullptr);
            break;

        case '|':
            add_token(lexer, match(lexer, '=') ? TT_OR_EQUALS : TT_OR, nullptr);
            break;

        case '^':
            add_token(lexer, match(lexer, '=') ? TT_XOR_EQUALS : TT_XOR, nullptr);
            break;

        case '<':
            add_token(lexer, match(lexer, '=') ? TT_LESSER_THAN_EQUALS : TT_LESSER_THAN, nullptr);
            break;

        case '>':
            add_token(lexer, match(lexer, '=') ? TT_GREATER_THAN_EQUALS : TT_GREATER_THAN, nullptr);
            break;

        case '=':
            add_token(lexer, match(lexer, '=') ? TT_EQUALS : TT_ASSIGN, nullptr);
            break;

        case '!':
            add_token(lexer, match(lexer, '=') ? TT_NOT_EQUALS : TT_NOT, nullptr);
            break;

        case ' ':
        case '\r':
        case '\t': break;

        case '\n':
            lexer->line++;
            break;

        default:
        {
            if (isdigit(character))
                scan_number(lexer);

            else if (isalpha(character))
                scan_identifier(lexer);

            else
                fprintf(stderr, "Unexpected character: %c\n", character);

            break;
        }
    }
}

void scan_tokens(lexer_t* lexer)
{
    while (!is_at_end(lexer))
    {
        lexer->start = lexer->current;
        scan_token(lexer);
    }

    const auto eof_token = init_token(TT_EOF, "", nullptr, lexer->line);
    lexer->tokens[lexer->token_count++] = eof_token;
}
