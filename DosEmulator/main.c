#include <stdio.h>
#include <malloc.h>
#include "registers.h"
#include "memory.h"
#include <math.h>

int parse(byte *memory, int memSize){
    int i = 0;
    while(i < memSize){
        if(memory[i] == 0x66 || memory[i] ==  0x67 || memory[i] == 0x26){
            printf("%02x ", memory[i]);
            i++;
        }
        switch (memory[i]){
            case 0xb8: printf("%02x ", memory[i]); i++; break;
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