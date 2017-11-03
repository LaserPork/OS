#include "registers.h"
#include "memory.h"
#include <stdio.h>
#include <math.h>
#include <mem.h>
#include <stdlib.h>


void execAddR8toRM8(byte *memory,registers* reg){
    if(LOGGER){
        printf("AddR8toRM8\n");
    }
    reg->ip+=2;
}
void execAdd(byte *memory,registers* reg){
    if(LOGGER){
        printf("Add\n");
    }
    reg->ip+=2;
}
void execXor(byte *memory,registers* reg){
    wholeRegister *destinationRegister,*sourceRegister;
    if(LOGGER){
        printf("Xor\n");
    }
    if(reg->instructionOverride == operandOverride){
        reg->instructionOverride = 0;
        reg->ip+=1;
        destinationRegister = (wholeRegister*)getRegister(getRMField(memory[reg->ip]),reg);
        sourceRegister = (wholeRegister*)getRegister(getModifier(memory[reg->ip]),reg);
        *destinationRegister = *sourceRegister ^ *destinationRegister;
        reg->ip+=1;
    }else{
        printf("Xor without operand override index was not implemented");
        exit(-1);
    }
}
void execIncrementEDX(byte *memory,registers* reg){
    if(LOGGER){
        printf("IncrementEDX\n");
    }
    reg->ip++;
}
void execIncrementEBX(byte *memory,registers* reg){
    if(LOGGER){
        printf("IncrementEBX\n");
    }
    reg->ip++;
}
void execDecrementECX(byte *memory,registers* reg){
    if(LOGGER){
        printf("DecrementECX\n");
    }
    reg->ip++;
}
void execJumpNotEqual(byte *memory,registers* reg){
    if(LOGGER){
        printf("JumpNotEqual\n");
    }
    reg->ip+=2;
}
void execJumpNotParity(byte *memory,registers* reg){
    if(LOGGER){
        printf("JumpNotParity\n");
    }
    reg->ip++;
}
void execCompare(byte *memory,registers* reg){
    if(LOGGER){
        printf("Compare\n");
    }
    reg->ip+=3;
}
void execMoveToR8(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveToR8\n");
    }
    reg->ip+=2;
    /* muze byt jine*/
}
void execMoveFromSegment(byte *memory,registers* reg){
    halfRegister *destinationRegister,*segmentRegister;
    if(LOGGER){
        printf("MoveFromSegment\n");
    }
    reg->ip+=1;
    if(getAdressingMode(memory[reg->ip])==3){
        destinationRegister = getRegister(getRMField(memory[reg->ip]),reg);
        segmentRegister = getSegment(getModifier(memory[reg->ip]),reg);
        *destinationRegister = *segmentRegister;
    }else{
        if(LOGGER){
            printf("Unimplemented Addressing mode\n");
            exit(-1);
        }
    }
    reg->ip+=1;
}
void execMoveToSegment(byte *memory,registers* reg){
    halfRegister *sourceRegister,*segmentRegister;
    if(LOGGER){
        printf("MoveToSegment\n");
    }
    reg->ip+=1;
    if(getAdressingMode(memory[reg->ip])==3){
        sourceRegister = getRegister(getRMField(memory[reg->ip]),reg);
        segmentRegister = getSegment(getModifier(memory[reg->ip]),reg);
        *segmentRegister = *sourceRegister;
    }else{
        if(LOGGER){
            printf("Unimplemented Addressing mode\n");
            exit(-1);
        }
    }
    reg->ip+=1;
}
void execMoveAH(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveAH\n");
    }
    reg->ip++;
    reg->ah = memory[reg->ip++];
    reg->ip+=2;
}
void execMoveAX(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveAX\n");
    }
    reg->ip++;
    reg->ax = memory[reg->ip++];
    reg->ax += memory[reg->ip++]*0x100;
}
void execMoveDX(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveDX\n");
    }
    reg->ip++;
    reg->dx = memory[reg->ip++];
    reg->dx += memory[reg->ip++]*0x100;
}
void execMoveBX(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveBX\n");
    }
    reg->ip++;
    reg->bx = memory[reg->ip++];
    reg->bx += memory[reg->ip++]*0x100;
}
void execMoveSI(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveSI\n");
    }
    reg->ip++;
    reg->si = memory[reg->ip++];
    reg->si += memory[reg->ip++]*0x100;
}
void execMoveDI(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveDI\n");
    }
    reg->ip++;
    reg->di = memory[reg->ip++];
    reg->di += memory[reg->ip++]*0x100;
}
void execMoveIMM16toRM16(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveIMM16toRM16\n");
    }
    reg->ip+=6;
}
int execInterrupt(byte *memory,registers* reg){
    if(LOGGER){
        printf("Interrupt\n");
    }
    reg->ip++;
    if(memory[reg->ip] == 0x10){
        if(LOGGER){
            printf("->Setting screen mode\n");
        }
        memset(memory+displayPointer,0,80*25*2);
        reg->ip++;
        return 10;
    }else if(memory[reg->ip] == 0x20){
        if(LOGGER){
            printf("->Quitting\n");
        }
        return 20;
    }else if(memory[reg->ip] == 0x21){
        return 21;
    }else{
        return -1;
    }
}
void execJump(byte *memory,registers* reg){
    if(LOGGER){
        printf("Jump\n");
    }
    reg->ip+=2;
}
void execIncrement(byte *memory,registers* reg){
    if(LOGGER){
        printf("Increment\n");
    }
    reg->ip+=2;
}

void printMemory(byte *memory, int memSize) {
    int i;
    printf("MEMORY DUMP: %d bytes\n",memSize);
    for (i = codeOffset; i < (codeOffset+memSize); i++) {
        printf("%02X", memory[i]);
    }
    printf("\n");
}

void printByte(byte b){
    int i;

    printf("%02X\n", b);

    for(i=0;i<8;i++){
        printf("%i", b & 0x01);
        b = b >> 1;
        if(i==2){
            printf(" ");
        }
        if(i==5){
            printf(" ");
        }
    }
    printf("\n", b);
}

int getRMField(byte addrMode){
    return addrMode&7;
}

int getAdressingMode(byte addrMode){
    return addrMode>> 6;
}

int getModifier(byte addrMode){
    return (addrMode>>3)&7;
}

halfRegister* getRegister(int correctPartOfAddrMode, registers* reg){
    switch (correctPartOfAddrMode)
    {
        case 0: return &reg->ax;
        case 1: return &reg->cx;
        case 2: return &reg->dx;
        case 3: return &reg->bx;
        case 4: return &reg->sp;
        case 5: return &reg->di;
        case 6: return &reg->si;
        case 7: return &reg->bx;
        default:
            if(LOGGER){printf("Unknown destination register\n");}
            exit(-1);
    }

}

halfRegister* getSegment(int correctPartOfAddrMode, registers* reg){
    switch (correctPartOfAddrMode)
    {
        case 0: return &reg->es;
        case 1: return &reg->cs;
        case 3: return &reg->ds;
        default:
            if(LOGGER){printf("Unknown segment register\n");}
            exit(-1);
    }
}