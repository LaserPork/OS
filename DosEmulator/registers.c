#include <stdio.h>
#include "registers.h"

void printRegisters(registers* reg){
    printf("%x\n",reg->eax);
    printf("%x\n",reg->ebx);
    printf("%x\n",reg->ecx);
    printf("%x\n",reg->edx);
}

void initRegisters(registers* reg){
    reg->eax = 0;
    reg->al = 1;
    reg->ah = 1;
    reg->ax = 1;
    reg->ebx = 0;
    reg->ecx = 0;
    reg->edx = 0;
}