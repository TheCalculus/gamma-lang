#include <stdio.h>
#include <stdlib.h>

#include "reader.c"
#include "tokenizer.c"

#define STACK_SIZE 10
#define MAXIMUM_BYTECODE 10
#define MAXIMUM_BYTECODE_DEPTH 3 // BIN_ADDER 1 BIN_ADDER 2 BIN_ADDER 3 (MAX)
                                 // 1 + 2 + 3 + (MAX)

int parseint(char *target) { int index = -1; int value = 0;
    while (target[++index] != '\0')
        value = value * 10 + (target[index] - 48);

    return value;
}

typedef enum {
    ADD_STACK, // ADD to STACK
    GET_STACK,
    REM_STACK,
    MOD_STACK,
    FOC_STACK,
    OPR_ADD,
    OPR_SUB,
    OPR_MUL,
    OPR_DIV
} Command;

struct Instruction {
  Command purpose;
  char* data;
  struct Instruction* link;
};

void printInstructionTree(struct Instruction* instruction) {
    printf("Printing instruction tree...\n");
    char operations[4] = {'+', '-', '*', '/'};
    
    while (instruction != NULL) {
        printf("%c%s", operations[-5 + instruction->purpose], instruction->data);
        instruction = instruction->link;
    }

    printf("\n");
}

void appendToList(struct Instruction **instruction, Command purpose, char* data) {
    struct Instruction *newNode = (struct Instruction *)malloc(sizeof(struct Instruction));

    newNode->purpose = purpose;
    newNode->data = strdup(data);
    newNode->link = *instruction;
    
    *instruction = newNode;
} 

int INSTRUCTION_INDEX = -1;

int main() {
    int bufferSize;
    FILE *f = fopen("test.gamma", "rb");   // from stdio
    char *buffer = reader(f, &bufferSize); // from reader.c

    Token tokens[bufferSize];

    tokenizerInitialisation.bufferSize = bufferSize;
    tokenize(buffer, tokens); // from tokenizer.c

    int tokenizerIndex = -1;
    Token* beginning = &tokens[0];

    while (tokens[++tokenizerIndex].type != THE_EOF) {
        TokenType type = tokens[tokenizerIndex].type;

        switch (type) {
            case EXP_DEF:
                // printf("ADD_STACK %s %s\n", (beginning + tokenizerIndex + 1)->value, (beginning + tokenizerIndex + 5)->value);
                break;
            case EXP_ASG:
                if (tokens[tokenizerIndex - 2].type == TYP_ANN) continue;
                
                int RHSindex = 0;
                struct Instruction *instruction = NULL;

                Command command = OPR_ADD;

                while (tokens[tokenizerIndex + (++RHSindex)].type != THE_EOI) {
                    Token RHScurr = *(beginning + tokenizerIndex + RHSindex);

                    if (RHScurr.type == KWD_INT || RHScurr.type == IDENTIF) {
                        appendToList(&instruction, command, RHScurr.value);
                        continue; 
                    }
                }

                printInstructionTree(instruction);
                
                break;
        }
    }

    return 0;
}
