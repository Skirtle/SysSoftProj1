// COP 3402 Fall 2020
// Project 1: P-Machine
// Team:
//  Dalton Kajander (da009211)
//  Shawn Guydeene (sh054884)

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_HEIGHT 1000
#define MAX_CODE_LENGTH 500

// Structs
typedef struct {
    int op; // Opcode
    int r; // R
    int l; // L
    int m; // M
} Instruction;

// Prototypes
Instruction* getInstructionFromFile(FILE* file, int *len);

// Main function
int main(int argc, char *argv[]) {
    /* Helpful information
    * argv[0]: .exe location
    * argv[1]: 1st actual argument (should be file name)
    */

   int SP = MAX_STACK_HEIGHT, BP = SP - 1, PC = 0, IR = 0;
   int length, i;
   char* filename = argv[1];
   FILE* ipf = fopen(filename, "r"); //Opens the command line text file given

    if (ipf == NULL) { //If the file name is wrong, or file does not exist, return 1 and exit
        printf("Filename \"%s\" not valid. FILE* ipf is NULL", filename);
        return 1;
    }

    Instruction* prog = getInstructionFromFile(ipf, &length);

    for (i = 0; i < length; i++) {
        // Fetch cycle:
        int IR = PC;
        PC += 1;

        Instruction* curr = &prog[IR];
        // Execute cycle:
        switch(curr->op) {
            case(1):
                
                break;
            case(2):
                
                break;
            case(3):
                
                break;
            case(4):
                
                break;
            case(5):
                
                break;
            case(6):
                
                break;
            case(7):
                
                break;
            case(8):
                
                break;
            case(9):
                
                break;
            case(10):
                
                break;
            case(11):
                
                break;
            case(12):
                
                break;
            case(13):
                
                break;
            case(14):
                
                break;
            case(15):
                
                break;
            case(16):
                
                break;
            case(17):
                
                break;
            case(18):
                
                break;
            case(19):
                
                break;
            case(20):
                
                break;
            case(21):
                
                break;
            case(22):
                
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
        fscanf(file, "%d %d %d %d", &temp.op, &temp.r, &temp.l, &temp.m);
        program[i] = temp;
    }

    return program;
}
