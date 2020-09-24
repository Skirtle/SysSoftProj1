// COP 3402 Fall 2020
// Project 1: P-Machine
// Team:
//  Dalton Kajander (da009211)
//  Shawn Guydeene (sh054884)

#include <stdio.h>
#include <stdlib.h>

// Defines and globals
#define MAX_STACK_HEIGHT 1000
#define MAX_CODE_LENGTH 500

// Structs
typedef struct {
    int OP; // Opcode
    int R; // R
    int L; // L
    int M; // M
} Instruction;

// Prototypes
Instruction* getInstructionFromFile(FILE* file, int *len);
int base(int l, int base, int* stack);

// Main function
int main(int argc, char *argv[]) {
    /* Helpful information
    * argv[0]: .exe location
    * argv[1]: 1st actual argument (should be file name)
    */

   int SP = MAX_STACK_HEIGHT, BP = SP - 1, PC = 0, IR = 0;
   int* stack = (int *)calloc(MAX_STACK_HEIGHT, sizeof(int));
   int* RF = (int *)calloc(8, sizeof(int));
   int length, i, halt = 1;
   char* filename = argv[1];
   FILE* ipf = fopen(filename, "r"); //Opens the command line text file given

    if (ipf == NULL) { //If the file name is wrong, or file does not exist, return 1 and exit
        printf("Filename \"%s\" not valid. FILE* ipf is NULL", filename);
        return 1;
    }

    Instruction* prog = getInstructionFromFile(ipf, &length);

    while (halt) {
        // Fetch cycle:
        int IR = PC;
        PC += 1;

        Instruction* curr = &prog[IR];
        // Execute cycle:
        switch(curr->OP) {
            case(1):
                RF[curr->R] = curr->M;
                break;
            case(2):
                SP = BP +1;
                BP = stack[SP-2];
                PC = stack[SP-3];
                break;
            case(3):
                RF[curr->R] = stack[base(curr->L, BP, stack) - curr->M];
                break;
            case(4):
                stack[base(curr->L, BP, stack) - curr->M] = RF[curr->R];
                break;
            case(5):
                stack[SP-1] = base(curr->L, BP, stack);
                stack[SP-2] = BP;
                stack[SP-3] = PC;
                BP = SP - 1;
                PC = curr->M;
                break;
            case(6):
                SP = SP - curr->M;
                break;
            case(7):
                PC = curr->M;
                break;
            case(8):
                if (RF[curr->R] == 0)  PC = curr->M;
                break;
            case(9):
                if(curr->M == 1)
                    printf("%d", RF[curr->R]);
                else if(curr->M == 2)
                    scanf("%d", RF[curr->R]);
                else if(curr->M == 3)
                    halt = 0;
                break;
            case(10):
                RF[curr->R] = -RF[curr->R];
                break;
            case(11):
                RF[curr->R] = RF[curr->L] + RF[curr->M];
                break;
            case(12):
                RF[curr->M] = RF[curr->L] - RF[curr->M];
                break;
            case(13):
                RF[curr->R] = RF[curr->L] * RF[curr->M];
                break;
            case(14):
                RF[curr->M] = RF[curr->L] / RF[curr->M];
                break;
            case(15):
                RF[curr->R] = RF[curr->R] % 2;
                break;
            case(16):
                RF[curr->M] = RF[curr->L] % RF[curr->M];
                break;
            case(17):
                RF[curr->R] = RF[curr->L] == RF[curr->M];
                break;
            case(18):
                RF[curr->M] = RF[curr->L] != RF[curr->M];
                break;
            case(19):
                RF[curr->R] = RF[curr->L] < RF[curr->M];
                break;
            case(20):
                RF[curr->M] = RF[curr->L] <= RF[curr->M];
                break;
            case(21):
                RF[curr->R] = RF[curr->L] > RF[curr->M];
                break;
            case(22):
                RF[curr->M] = RF[curr->L] >= RF[curr->M];
                break;
        }

    }

    free(prog);
    return 0;
}

// Function bodies
Instruction* getInstructionFromFile(FILE* file, int *len) {
    int i, c;
    int lines = 1;

    for (c = getc(file); c != EOF; c = getc(file)) {
        if (c == '\n') {
            lines++;
        }
    }
    *len = lines;
    rewind(file);

    Instruction* program = (Instruction*) calloc(lines, sizeof(Instruction));
    Instruction temp;
    for (i = 0; i < lines; i++) {
        fscanf(file, "%d %d %d %d", &temp.OP, &temp.R, &temp.L, &temp.M);
        program[i] = temp;
    }

    return program;
}

int base(int l, int base, int* stack) {
    int b1 = base;

    while(l > 0) {
        b1 = stack[b1];
        l--;
    }
    return b1;
}
