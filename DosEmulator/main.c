#include <stdio.h>
#include <malloc.h>
#include "registers.h"
#include "memory.h"
#include <math.h>

int parse(byte *memory, int memSize){
    int i = 0;
    while(i < memSize){
        if(memory[i] == segmentOverride || memory[i] ==  operandOverride || memory[i] == addressOverride){
            printf("%02x ", memory[i]);
            i++;
        }
        switch (memory[i]){
            case addR8toRM8:;
            case add:;
            case xor:;
            case incrementEDX:;
            case incrementEBX:;
            case decrementECX:;
            case jumpNotEqual:;
            case jumpNotParity:;
            case compare:;
            case moveToR8:;
            case moveFromSegment:;
            case moveToSegment:;
            case moveAH:;
            case moveAX:;
            case moveDX:;
            case moveBX:;
            case moveSI:;
            case moveDI:;
            case moveIMM16toRM16:;
            case interrupt:;
            case jump:;
            case increment:;
            default:printf("This virtualization doesn't use opcode %02x ", memory[i]);
        }
        printf("%02x ", memory[i]);
        i++;
        printf("%02x\n", memory[i]);
        i++;
    }
}
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
    parse(memory, memSize);
}


int main() {
    registers dosRegisters;
    initRegisters(&dosRegisters);
    loadFile();
    return 0;
}