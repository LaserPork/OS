#include "registers.h"
#include <stdio.h>
void printMemory(byte *memory, int memSize) {
    int i;
    printf("%d\n",0x100);
    printf("MEMORY DUMP: \n");
    for (i = 0; i < memSize; i++) {
        printf("%x", memory[i]);
    }
}