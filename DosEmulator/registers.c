#include <stdio.h>
#include "registers.h"
#include "memory.h"

void printRegisters(registers* reg){
    printf("  [    E_X    ]\n");
    printf("  [ _X ]       \n");
    printf("  L  H         \n");
    int i=0;
    while (i < sizeof(wholeRegister)*4)
    {
        if(i%2 == 0){
            printf("  ");
        }
        printf("%02X ", *((byte *)reg+i));
        i++;
        if(i%4 == 0){
            printf("\n");
        }
    }
    printf("IP: %04X\n", reg->ip);
    printf("CS: %04X\n", reg->cs);
    printf("DS: %04X\n", reg->ds);
    printf("SS: %04X\n", reg->ss);
    printf("DI: %04X\n", reg->di);
    printf("SI: %04X\n", reg->si);


}

void initRegisters(registers* reg){
    reg->eax = 0xFFFFFFFF;
    reg->ebx = 0xFFFFFFFF;
    reg->ecx = 0xFFFFFFFF;
    reg->edx = 0xFFFFFFFF;
    reg->cs = 0x0000;//code segment
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