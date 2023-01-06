/*
 * TOKENIZER / LEXICAL ANALYZER - tokenizer.c
 * Iterates through input *.gamma file and extracts tokens of types from keywords.c
 * Array of tokens returned format TokenType[bufferSize].
 * */

#include <stdlib.h>

#include "keywords.c" 
#include "trie.c"

#define MAXIMUM_LENGTH 7 

typedef struct INIT_OPTIONS {
    int bufferSize;
} INIT_OPTIONS;

INIT_OPTIONS tokenizerInitialisation;

struct TrieNode* root; // from trie.c

typedef struct { 
    TokenType type; // from keywords.c
    char value[MAXIMUM_LENGTH];
} Token; 

typedef struct {
    char* input;
    int size;
    Token activeToken;

    int position;
} Lexer;

Lexer* newLexer(char* input) {
    Lexer* lexer = malloc(sizeof(Lexer));

    lexer->input = input;
    lexer->position = 0;
    lexer->activeToken = (Token) { THE_EOF, "" };

    return lexer;
}

void freeLexer(Lexer* lexer) { free(lexer); }

int isWhiteSpace(char ch)
{
    if ((ch == ' ') || (ch == '\t') || (ch == '\n') || (ch == '\v') || (ch == '\r') || (ch == '\f')) return 1;
    return 0;
}

int isDigit(char ch) { return (ch >= '0' && ch <= '9'); }

int isAlnum(char ch) { return (isDigit(ch) || (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')); }

void skipWhitespace(Lexer* lexer) {
    while (isWhiteSpace(lexer->input[lexer->position]))
        lexer->position++;
}

void scanValue(Lexer* lexer, char activeCharacter, char* value) {
    int value_pos = -1;

    while (isAlnum(activeCharacter)) {
        value[++value_pos] = activeCharacter;
        activeCharacter = lexer->input[++lexer->position];
    }

    --lexer->position;

    value[value_pos + 1] = '\0';
}

Token nextToken(Lexer* lexer) {
    lexer->position > 0 ? lexer->position++ : 0;
    skipWhitespace(lexer);
    char activeCharacter = lexer->input[lexer->position];

    if (lexer->position >= tokenizerInitialisation.bufferSize - 1)
        return (Token) { THE_EOF, "<EOF>" };

    switch (activeCharacter) {
        case(':'):
            return (Token) { TYP_ANN, ':' };
        case(';'):
            return (Token) { THE_EOI, ';' };
        case('+'):
            return (Token) { ARM_PLU, '+' };
        case('-'):
            return (Token) { ARM_SUB, '-' };
        case('*'):
            return (Token) { ARM_MUL, '*' };
        case('/'):
            return (Token) { ARM_DIV, '/' };
        case('%'):
            return (Token) { ARM_MOD, '%' };
        case('='): // TODO: add case for checking equivalence (==)
            return (Token) { EXP_ASG, '=' };
        case('{'):
            return (Token) { BLK_BEG, '{' };
        case('}'):
            return (Token) { BLK_END, '}' };
        case('('):
            return (Token) { EXP_BEG, '(' };
        case(')'):
            return (Token) { EXP_END, ')' };
    }

    char value[MAXIMUM_LENGTH];
    scanValue(lexer, activeCharacter, value);
    
    Token activeToken;
    activeToken.type = (TokenType) IDENTIF;
    memcpy(activeToken.value, value, MAXIMUM_LENGTH);

    if (isDigit(activeCharacter)) {
        activeToken.type = (TokenType) KWD_INT;
        return activeToken;
    }

    int isKeyword = search(root, value);

    if (isKeyword)
        activeToken.type = (TokenType) mapKeyword(value);

    return activeToken;
}

void tokenize(char* buffer, Token tokenList[]) {
    root = getNode();
                                          
    insert(root, "float");
    insert(root, "fn");
    insert(root, "int");
    insert(root, "null");
    insert(root, "return");
    insert(root, "undefined");
    insert(root, "var");

    Lexer* lex = newLexer(buffer);
    int index = -1;
    int isEOF = 0;

    while (!isEOF) {
        Token token = nextToken(lex);
        tokenList[++index] = token;

        isEOF = (token.type == THE_EOF);
    }

    free(root);
    freeLexer(lex);
    free(buffer);
}
