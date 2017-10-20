#include <stdio.h>
#include <malloc.h>
#include "registers.h"
#include "memory.h"
#include <math.h>

int loadFile(){
    FILE *filePointer;
    char *filename = "VB08.COM";
    filePointer = fopen(filename,"rb");
    byte *memory;
    int c,memSize = 0;
    memory = malloc((int)pow(2,10) * sizeof(byte));
    if (memory == NULL)
    {
        fprintf(stderr, "Virtual memory could not be allocated.\n");
        return(-1);
    }
    if (filePointer == NULL)
    {
        printf("File could not be opened.\n");
        return -1;
    }
    while ((c = fgetc(filePointer)) != EOF)
    {
        memory[memSize++] = (byte) c;
    }
    printMemory(memory, memSize);
}


int main() {
    registers dosRegisters;
    initRegisters(&dosRegisters);
    loadFile();
    return 0;
}