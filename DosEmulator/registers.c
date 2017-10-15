#include <stdio.h>
#include "registers.h"

void printRegisters(registers* reg){
    printf("[    E_X    ]\n");
    printf("[ _X ]       \n");
    printf("L  H         \n");
    int i=0;
    while (i < sizeof(registers))
    {
        printf("%02X ", *((byte *)reg+i));
        i++;
        if(i%4 == 0){
            printf("\n");
        }else if(i%2 == 0){
            printf(" ");
        }
    }

}

void initRegisters(registers* reg){
    reg->eax = 0xFFFFFFFF;
    reg->ebx = 0xFFFFFFFF;
    reg->ecx = 0xFFFFFFFF;
    reg->edx = 0xFFFFFFFF;
    reg->al = 0x10;
    reg->bx = 0xAAAA;
}