// COP 3402 Fall 2020
// Project 1: P-Machine
// Team:
//  Dalton Kajander (da009211)
//  Shawn Guydeene (sh054884)

#include <stdio.h>
#include <stdlib.h>

// Structs
typedef struct {
    int op; // Opcode
    int r; // R
    int l; // L
    int m; // M
} Instruction;

// Prototypes
Instruction* getInstructionFromFile(FILE* file, int *len);

int main(int argc, char *argv[]) {
    /* Helpful information
    * argv[0]: .exe location
    * argv[1]: 1st actual argument (should be file name)
    */

   int length;
   char* filename = argv[1];
   FILE* ipf = fopen(filename, "r"); //Opens the command line text file given

    if (ipf == NULL) { //If the file name is wrong, or file does not exist, return 1 and exit
        printf("Filename \"%s\" not valid. FILE* ipf is NULL", filename);
        return 1;
    }

    getInstructionFromFile(ipf, &length);

    return 0;
}

Instruction* getInstructionFromFile(FILE* file, int *len) {

    int i, c, lines;
    int count = 0;


    while(1) {
        c = fgetc(file);
        if (c == EOF || c == '\n') {
            break;
        }
        if (c != ' ') {
            count++;
        }
    }

    lines = count/4;

    printf("Length (lines): %d\n", lines);

    return NULL;
}