#include <stdio.h>
#include <stdlib.h>

#include "reader.c"
#include "tokenizer.c"

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

struct Instruction newInstruction(Command purpose, char* data, struct Instruction* link) {
    return (struct Instruction) { purpose, data, link };
}

#define MAXIMUM_INSTRUCTIONS 100
struct Instruction* EXECUTION_PATH[MAXIMUM_INSTRUCTIONS];
int instruction_capacity = -1;

void appendToList(Command purpose, char* data, struct Instruction** instruction) {
    struct Instruction* newNode = (struct Instruction*)malloc(sizeof(struct Instruction));

    newNode->purpose = purpose;
    newNode->data = strdup(data);
    newNode->link = *instruction;
    
    *instruction = newNode;
}

void addToPath(struct Instruction* instruction) {
    if (instruction_capacity != MAXIMUM_INSTRUCTIONS)
        EXECUTION_PATH[++instruction_capacity] = instruction;
    return;
}

void generateBytecode() {
    // let generateBytecode open and read the file, for now
    int bufferSize;
    FILE* f = fopen("test.gamma", "rb");   // from stdio
    char* buffer = reader(f, &bufferSize); // from reader.c

    Token tokens[bufferSize];

    tokenizerInitialisation.bufferSize = bufferSize;
    tokenize(buffer, tokens); // from tokenizer.c

    int tokenizerIndex = -1;
    Token* beginning = &tokens[0];

    while (tokens[++tokenizerIndex].type != THE_EOF) {
        TokenType type = tokens[tokenizerIndex].type;

        if (type == EXP_DEF) {
            struct Instruction definition = newInstruction(
                    (Command) ADD_STACK,
                    (beginning + tokenizerIndex + 1)->value,
                    NULL
            );
            struct Instruction focus = newInstruction(
                    (Command) FOC_STACK,
                    (beginning + tokenizerIndex + 1)->value,
                    NULL
            );
            struct Instruction modification = newInstruction(
                    (Command) MOD_STACK,
                    (beginning + tokenizerIndex + 5)->value,
                    NULL
            );

            addToPath(&definition);
            addToPath(&focus);
            addToPath(&modification);

            printf("ADD_STACK %s\n", (beginning + tokenizerIndex + 1)->value);
            printf("FOC_STACK %s\n", (beginning + tokenizerIndex + 1)->value);
            printf("MOD_STACK %s\n\n", (beginning + tokenizerIndex + 5)->value);
        }
        else if (type == EXP_ASG) {
            if (tokens[tokenizerIndex - 2].type == TYP_ANN) continue;
            
            int RHSindex = 0;

            struct Instruction* nullins = NULL;

            struct Instruction focus = newInstruction(
                    (Command) FOC_STACK,
                    (beginning + tokenizerIndex - 1)->value,
                    NULL
            );
            struct Instruction modification = newInstruction(
                    (Command) MOD_STACK,
                    NULL,
                    nullins
            );

            Command command = OPR_ADD;
            int res = 0;

            while (tokens[tokenizerIndex + (++RHSindex)].type != THE_EOI) {
                Token RHScurr = *(beginning + tokenizerIndex + RHSindex);

                if (RHScurr.type == KWD_INT || RHScurr.type == IDENTIF) {
                    appendToList(command, RHScurr.value, &modification.link);
                    switch (modification.link->purpose) {
                        case OPR_ADD: 
                            res += atoi(modification.link->data);
                            break;
                        case OPR_SUB:
                            res -= atoi(modification.link->data); 
                            break;
                        case OPR_MUL:
                            res *= atoi(modification.link->data);
                            break;
                        case OPR_DIV:
                            res /= atoi(modification.link->data);
                            break;
                    }
                    continue; 
                }

                switch (RHScurr.type) {
                    case ARM_PLU: command = OPR_ADD; break;
                    case ARM_SUB: command = OPR_SUB; break;
                    case ARM_MUL: command = OPR_MUL; break;
                    case ARM_DIV: command = OPR_DIV; break;
                }

                modification.link->purpose = command;
            }

            addToPath(&focus); 
            addToPath(&modification); 

            printf("FOC_STACK %s\n", (beginning + tokenizerIndex - 1)->value);
            printf("MOD_STACK (");
            printInstructionTree(modification.link);
            printf(" ) (%d)\n", res);
        }
    }
}

int main() {
    generateBytecode(); // generates mini-instructions that are then run by a parser in the same file
    return 0;
}
