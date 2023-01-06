#include <stdio.h>
#include <stdlib.h>

#include "reader.c"
#include "tokenizer.c"

#define NUM_INSTRUCTIONS 7
#define MAX_EXECUTIONS 10

typedef enum {
    ADDS, // add stack
    REMS, // remove stack
    MODS, // modify stack (assignment & reassignment) 
    GETS, // get stack 
    INCR, // increment
    DECR, // decrement
    ADDR, // pointer
    ALLC, // allocate
    RLLC, // reallocate
    PROC, // procedure
} PURPOSE;

typedef struct {
    union {
        int INT_VALUE;
        char* STR_VALUE;
    } value;
    int activeValue;
} ARGUMENT;

typedef struct {
    PURPOSE purpose;
    int num_args;
    ARGUMENT* args;
} InstructionTemplate;

void GenerateInstruction(TokenType type, InstructionTemplate* CURR_INSTRUCTION, Token* tokenList, int index);

InstructionTemplate POSSIBLE_INSTRUCTIONS[NUM_INSTRUCTIONS] = {
    { ADDS, 2, (ARGUMENT []) { { .value.STR_VALUE = "null", .activeValue = 1 }, { .value.INT_VALUE = 0, .activeValue = 0 } } },
    { REMS, 1, (ARGUMENT []) { { .value.STR_VALUE = "null", .activeValue = 1 } } },
    { MODS, 2, (ARGUMENT []) { { .value.STR_VALUE = "null", .activeValue = 1 }, { .value.INT_VALUE = 0, .activeValue = 0 } } },
    { GETS, 1, (ARGUMENT []) { { .value.STR_VALUE = "null", .activeValue = 1 } } },
    { INCR, 2, (ARGUMENT []) { { .value.STR_VALUE = "null", .activeValue = 1 }, { .value.INT_VALUE = 0, .activeValue = 1 } } },
    { DECR, 2, (ARGUMENT []) { { .value.STR_VALUE = "null", .activeValue = 1 }, { .value.INT_VALUE = 0, .activeValue = 1 } } },
    { ADDR, 1, (ARGUMENT []) { { .value.STR_VALUE = "null", .activeValue = 1 } } },
};

InstructionTemplate MAP_INSTRUCTION(PURPOSE purpose) {
    for (int i = 0; i < NUM_INSTRUCTIONS; ++i)
        if (POSSIBLE_INSTRUCTIONS[i].purpose == purpose)
            return POSSIBLE_INSTRUCTIONS[i];
}

InstructionTemplate EXECUTION_PATH[MAX_EXECUTIONS];
int EXECUTION_CAPACITY = MAX_EXECUTIONS + 1;

int parseint(char *target) {
    int index = -1;
    int value = 0;

    while (target[++index] != '\0') {
        value = value * 10 + (target[index] - 48);
    }

    return value;
}

void GenerateInstruction(TokenType type, InstructionTemplate* CURR_INSTRUCTION, Token* tokenList, int index) {
    switch (type) {
        case EXP_DEF:
            (*CURR_INSTRUCTION) = MAP_INSTRUCTION((PURPOSE) ADDS);

            (*CURR_INSTRUCTION).args[0].value.STR_VALUE = tokenList[index + 1].value;
            (*CURR_INSTRUCTION).args[1].value.INT_VALUE = parseint(tokenList[index + 5].value);

            EXECUTION_PATH[MAX_EXECUTIONS - (--EXECUTION_CAPACITY)] = (*CURR_INSTRUCTION);

            printf("ADDS %s %d\n", (*CURR_INSTRUCTION).args[0].value.STR_VALUE, (*CURR_INSTRUCTION).args[1].value.INT_VALUE);

            break;
        case EXP_ASG:
            if (tokenList[index - 2].type != TYP_ANN) {
                int rhs_start = index + 1;
                int rhs_end = index + 1;

                while (tokenList[rhs_end].type != THE_EOI)
                    ++rhs_end;

                int result = 0;
                for (int i = rhs_start; i <= rhs_end; i++) {
                    if (tokenList[i].type == KWD_INT) {
                        result += parseint(tokenList[i].value);
                    } else if (tokenList[i].type == ARM_PLU) {
                        InstructionTemplate INCR_INSTRUCTION = MAP_INSTRUCTION((PURPOSE) INCR);
                        INCR_INSTRUCTION.args[0].value.STR_VALUE = tokenList[i - 1].value;
                        INCR_INSTRUCTION.args[1].value.INT_VALUE = parseint(tokenList[i + 1].value);
                        EXECUTION_PATH[MAX_EXECUTIONS - (--EXECUTION_CAPACITY)] = INCR_INSTRUCTION;
                        printf("INCR %s %d\n", INCR_INSTRUCTION.args[0].value.STR_VALUE, INCR_INSTRUCTION.args[1].value.INT_VALUE);
                    } else if (tokenList[i].type == IDENTIF) {
                        InstructionTemplate GETS_INSTRUCTION = MAP_INSTRUCTION((PURPOSE) GETS);
                        GETS_INSTRUCTION.args[0].value.STR_VALUE = tokenList[i].value;
                        EXECUTION_PATH[MAX_EXECUTIONS - (--EXECUTION_CAPACITY)] = GETS_INSTRUCTION;
                        printf("GETS %s\n", GETS_INSTRUCTION.args[0].value.STR_VALUE);
                    }
                }

                (*CURR_INSTRUCTION) = MAP_INSTRUCTION((PURPOSE) MODS);
                (*CURR_INSTRUCTION).args[0].value.STR_VALUE = tokenList[index - 1].value;
                (*CURR_INSTRUCTION).args[1].value.INT_VALUE = result;
                EXECUTION_PATH[MAX_EXECUTIONS - (--EXECUTION_CAPACITY)] = (*CURR_INSTRUCTION);

                printf("MODS %s %d\n", (*CURR_INSTRUCTION).args[0].value.STR_VALUE, (*CURR_INSTRUCTION).args[1].value.INT_VALUE);
            }

            break;
    }
}

int main() {
    int bufferSize;
    FILE *f = fopen("test.gamma", "rb");   // from stdio
    char *buffer = reader(f, &bufferSize); // from reader.c

    Token tokenList[bufferSize];
    int index = -1;

    tokenizerInitialisation.bufferSize = bufferSize;
    tokenize(buffer, tokenList); // from tokenizer.c

//    (TokenType type, InstructionTemplate* CURR_INSTRUCTION, Token** tokenList, int index)

    while (tokenList[++index].type != THE_EOF) {
        TokenType type = tokenList[index].type;
        InstructionTemplate CURR_INSTRUCTION;
        
        GenerateInstruction(type, &CURR_INSTRUCTION, tokenList, index);
    }

    return 0;
}
