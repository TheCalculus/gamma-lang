#include "bytecode.c"

/*
 * PARSER - parser.c
 * reads bytecode generated from bytecode.c and runs commands.
 * Includes a 'stack' that reads variable definitions and allocates memory on the heap for variable data to be stored. This data would not be freed until the program finishes executing.
 * */

typedef union {
    int VALUE_INT;
    char* VALUE_STR;
} ALMIGHTY_VALUE;

#define MAX_STACK_SIZE 10

typedef struct {
    char* identifier;
    ALMIGHTY_VALUE value;
} STACK_ITEM;

STACK_ITEM GAMMA_STACK[MAX_STACK_SIZE] = {};
int STACK_CAPACITY = -1;

int cmp(char* str1, char* str2) {
    int index = -1;
    
    while (str1[++index] != '\0')
        if (str1[index] != str2[index]) return 0;

    return 1;
}

STACK_ITEM findInStack(char* identifier) {
    for (int i = 0; i <= STACK_CAPACITY; ++i) {
        if (cmp(GAMMA_STACK[i].identifier, identifier))
            return GAMMA_STACK[i];
    }

    return (STACK_ITEM) { "null", -46290 };
}

int parseint(char* target) {
    int index = -1;
    int value = 0;

    while (target[++index] != '\0') {
        value = value * 10 + (target[index] - 48);
    }

    return value;
}

int main() {
    int bytecodeSize;
    Instruction bytecode[MAX_EXECUTIONS] = {};
    generateBytecode(bytecode, &bytecodeSize);

    for (int i = 0; i < bytecodeSize; ++i) {
        if (bytecode->INSTRUCTION_TYPE == NEW_VAR) {
            printf("%s\n", bytecode->value);

            int* IDENTIFIER_VALUE = (int *)malloc(sizeof(int));
            *IDENTIFIER_VALUE = parseint(bytecode->value);

            GAMMA_STACK[++STACK_CAPACITY] = (STACK_ITEM) { bytecode->IDENTIFIER, *IDENTIFIER_VALUE };

            if (STACK_CAPACITY > MAX_STACK_SIZE) 
                printf("maximum stack size reached blah blah");

            continue;
        }
        if (bytecode->INSTRUCTION_TYPE == GET_VAR) {
            //    printf("Value of %s: %d\n", bytecode->IDENTIFIER, findInStack(bytecode[i].IDENTIFIER).value.VALUE_INT);

            continue;
        }
    }

    return 0;
}
