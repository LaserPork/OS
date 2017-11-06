#include <stdio.h>
#include "registers.h"
#include "memory.h"

void printRegisters(registers* reg){
    printf("[    E_X    ]\n");
    printf("[ _X ]       \n");
    printf("L  H         \n");
    int i=0;
    while (i < sizeof(registers))
    {
        printf("%02X ", *((byte *)reg+i));
        i++;
        if(i == 16) {
            printf("\n\n");
        }else if(i%4 == 0){
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
    reg->cs = 0x1234;//code segment
    reg->ds = 0x0000; //data segment
    reg->ss = 0x0000; //stack segment
    reg->es = 0x0000; //extra segment
    //INDEX REGISTERS
    reg->di = 0x0000; //destination index
    reg->si = 0x0000; //stack index snad nebudeme zasobnik potrebovat
    //POINTERS
    reg->sp = 0x0000; //stack pointer snad nebudeme zasobnik potrebovat
    reg->bp = 0x0000; //base pointer
    reg->ip = codeOffset;
    reg->operandOverride = 0;
    reg->addressOverride = 0;
    reg->segmentOverride = 0;
}