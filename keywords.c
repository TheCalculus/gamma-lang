/*
 * KEYWORDS - keywords.c
 * Contains enum with all possible keywords for language. Used by the lexical analyzer (tokenizer.c) to classify the 'type' of every single block of text in input *.gamma.
 * There are NUM_KEYWORDS keywords in enum TokenType.
 * */

typedef enum {
    ARM_DIV,
    ARM_MOD,
    ARM_MUL,
    ARM_PLU,
    ARM_SUB,
    BLK_BEG,
    BLK_END,
    EXP_ASG,
    EXP_BEG,
    EXP_DEF,
    EXP_END,
    IDENTIF,
    KWD_FLT,
    KWD_FUN,
    KWD_INT,
    KWD_NUL,
    KWD_RET,
    THE_EOF,
    THE_EOI,
    TYP_ANN,
    NUM_KEYWORDS, 
} TokenType;

struct KeywordMapping {
    char* keyword;
    TokenType value;
};

struct KeywordMapping keyword_mappings[] = {
    {"float", KWD_FLT},
    {"fn", KWD_FUN},
    {"int", KWD_INT},
    {"null", KWD_NUL},
    {"return", KWD_RET},
    {"var", EXP_DEF},
};

TokenType mapKeyword(char* keyword) {
    for (int i = 0; i < NUM_KEYWORDS; ++i)
        if (strcmp(keyword_mappings[i].keyword, keyword) == 0)
            return keyword_mappings[i].value;

    return IDENTIF;
}
