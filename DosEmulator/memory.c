#include "registers.h"
#include "memory.h"
#include <stdio.h>

int execAddR8toRM8(byte *memory,registers* reg){
    if(LOGGER){
        printf("AddR8toRM8\n");
    }
    reg->ip+=2;
}
int execAdd(byte *memory,registers* reg){
    if(LOGGER){
        printf("Add\n");
    }
    reg->ip+=2;
}
int execXor(byte *memory,registers* reg){
    if(LOGGER){
        printf("Xor\n");
    }
    reg->ip+=2;
}
int execIncrementEDX(byte *memory,registers* reg){
    if(LOGGER){
        printf("IncrementEDX\n");
    }
    reg->ip++;
}
int execIncrementEBX(byte *memory,registers* reg){
    if(LOGGER){
        printf("IncrementEBX\n");
    }
    reg->ip++;
}
int execDecrementECX(byte *memory,registers* reg){
    if(LOGGER){
        printf("DecrementECX\n");
    }
    reg->ip++;
}
int execJumpNotEqual(byte *memory,registers* reg){
    if(LOGGER){
        printf("JumpNotEqual\n");
    }
    reg->ip+=2;
}
int execJumpNotParity(byte *memory,registers* reg){
    if(LOGGER){
        printf("JumpNotParity\n");
    }
    reg->ip++;
}
int execCompare(byte *memory,registers* reg){
    if(LOGGER){
        printf("Compare\n");
    }
    reg->ip+=3;
}
int execMoveToR8(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveToR8\n");
    }
    reg->ip+=2;
    /* muze byt jine*/
}
int execMoveFromSegment(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveFromSegment\n");
    }
    reg->ip+=2;
}
int execMoveToSegment(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveToSegment\n");
    }
    reg->ip+=2;
}
int execMoveAH(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveAH\n");
    }
    reg->ip+=2;
}
int execMoveAX(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveAX\n");
    }
    reg->ip+=3;
}
int execMoveDX(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveDX\n");
    }
    reg->ip+=3;
}
int execMoveBX(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveBX\n");
    }
    reg->ip+=3;
}
int execMoveSI(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveSI\n");
    }
    reg->ip+=3;
}
int execMoveDI(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveDI\n");
    }
    reg->ip+=3;
}
int execMoveIMM16toRM16(byte *memory,registers* reg){
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
        reg->ip++;
    }
}
int execJump(byte *memory,registers* reg){
    if(LOGGER){
        printf("Jump\n");
    }
    reg->ip+=2;
}
int execIncrement(byte *memory,registers* reg){
    if(LOGGER){
        printf("Increment\n");
    }
    reg->ip+=2;
}

void printMemory(byte *memory, int memSize) {
    int i;
    printf("%d\n",0x100);
    printf("MEMORY DUMP: %d bytes\n",memSize);
    for (i = 0; i < memSize; i++) {
        printf("%02X", memory[i]);
    }
    printf("\n");
}