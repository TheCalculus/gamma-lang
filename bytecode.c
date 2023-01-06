#include <stdio.h>
#include <stdlib.h>

#include "reader.c"
#include "tokenizer.c"

int parseint(char *target) { int index = -1; int value = 0;
    while (target[++index] != '\0')
        value = value * 10 + (target[index] - 48);

    return value;
}

typedef enum {
    ADD_STACK,
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
    char* operations[4] = {"ADD", "SUBTRACT", "MULTIPLY", "DIVIDE"};
    
    while (instruction != NULL) {
        printf(" %s %s", operations[-5 + instruction->purpose], instruction->data);
        instruction = instruction->link;
    }
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
                printf("ADD_STACK %s %s\n", (beginning + tokenizerIndex + 1)->value, (beginning + tokenizerIndex + 5)->value);
                break;
            case EXP_ASG:
                if (tokens[tokenizerIndex - 2].type == TYP_ANN) continue;
                
                int RHSindex = 0;
                struct Instruction* instruction = NULL;

                Command command = OPR_ADD;

                while (tokens[tokenizerIndex + (++RHSindex)].type != THE_EOI) {
                    Token RHScurr = *(beginning + tokenizerIndex + RHSindex);

                    if (RHScurr.type == KWD_INT || RHScurr.type == IDENTIF) {
                        appendToList(&instruction, command, RHScurr.value);
                        continue; 
                    }

                    switch (RHScurr.type) {
                        case ARM_PLU: command = OPR_ADD; break;
                        case ARM_SUB: command = OPR_SUB; break;
                        case ARM_MUL: command = OPR_MUL; break;
                        case ARM_DIV: command = OPR_DIV; break;
                    }

                    instruction->purpose = command;
                }

                printf("MOD_STACK %s (", (beginning + tokenizerIndex - 1)->value);
                printInstructionTree(instruction);
                printf(" )\n");

                break;
        }
    }

    return 0;
}
