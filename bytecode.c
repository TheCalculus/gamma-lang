#include <stdio.h>
#include <stdlib.h>

#include "reader.c"
#include "tokenizer.c"

/*
 * BYTECODE GENERATOR - bytecode.c
 * generates series of instructions that are passed into parser.
 * The parser would run 'custom' commands in a virtual machine (like JVM).
 * TODO: parser converts bytecode into assembly which can then be run
 * */

#define MAX_EXECUTIONS 10
#define MAX_STACK_SIZE 10

typedef struct
{
    char *identifier;
    union value
    {
        int VALUE_INT;
        char *VALUE_STR;
    };
} STACK_ITEM;

STACK_ITEM GAMMA_STACK[MAX_STACK_SIZE] = {};
int STACK_CAPACITY = -1;

int cmp(char *str1, char *str2)
{
    int index = -1;

    while (str1[++index] != '\0')
        if (str1[index] != str2[index])
            return 0;

    return 1;
}

STACK_ITEM *findInStack(char *identifier)
{
    for (int i = 0; i <= STACK_CAPACITY; ++i)
        if (cmp(GAMMA_STACK[i].identifier, identifier))
            return &GAMMA_STACK[i];
    return &((STACK_ITEM){"null", -46290});
}

int parseint(char *target)
{
    int index = -1;
    int value = 0;

    while (target[++index] != '\0')
    {
        value = value * 10 + (target[index] - 48);
    }

    return value;
}

int EXECUTION_CAPACITY = -1;

int main()
{
    int errorCode = 0;

    int bufferSize;
    FILE *f = fopen("test.gamma", "rb");   // from stdio
    char *buffer = reader(f, &bufferSize); // from reader.c

    Token tokenList[bufferSize];
    int index = -1;

    tokenizerInitialisation.bufferSize = bufferSize;
    tokenize(buffer, tokenList); // from tokenizer.c

    while (tokenList[++index].type != THE_EOF && errorCode == 0)
    {
        TokenType type = tokenList[index].type;

        switch (type)
        {
        case EXP_DEF:
            // var x: int = 10, where var is EXP_DEF (and the current index)
            int *IDENTIFIER_VALUE = (int *)malloc(sizeof(int));
            *IDENTIFIER_VALUE = parseint(tokenList[index + 5].value);
            GAMMA_STACK[++STACK_CAPACITY] = (STACK_ITEM){tokenList[index + 1].value, *IDENTIFIER_VALUE};

            break;
        case EXP_ASG:
            // x = 12 <- EXP_ASG token is assigned in improper places, mainly EXP_DEF. Check for this before assignment.

            if (tokenList[index - 2].type != TYP_ANN)
            {
                STACK_ITEM *variable = findInStack(tokenList[index - 1].value);
                int inStack = !cmp(variable->identifier, "null");
                // ensure all code paths have a return value in findInStack, to prevent segfault
                if (inStack)
                {
                    (*variable).VALUE_INT = parseint(tokenList[index + 1].value);
                    printf("Value of %s: %d\n", tokenList[index - 1].value, (*findInStack(tokenList[index - 1].value)).VALUE_INT);
                    break;
                }
                printf("ReferenceError: Assignment to variable %s before initialization.\n", tokenList[index - 1].value);
                errorCode = 404;
            }
        case ARM_PLU:
            // x + y, where + is ARM_PLU
            if (tokenList[index - 1].type == IDENTIF)
            {
                int x = findInStack(tokenList[index - 1].value)->VALUE_INT;
                printf("%d", x + parseint(tokenList[index + 1].value));
            }

            if (tokenList[index + 1].type == IDENTIF)
            {
                int x = findInStack(tokenList[index + 1].value)->VALUE_INT;
                printf("%d", x + parseint(tokenList[index - 1].value));
            }
        }
    }
}
