#include "registers.h"
#include "memory.h"
#include <stdio.h>

int execAddR8toRM8(byte *memory,registers* reg){
    if(LOGGER){
        printf("AddR8toRM8\n");
    }
    reg->ip++;
}
int execAdd(byte *memory,registers* reg){
    if(LOGGER){
        printf("Add\n");
    }
    reg->ip++;
}
int execXor(byte *memory,registers* reg){
    if(LOGGER){
        printf("Xor\n");
    }
    reg->ip++;
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
    reg->ip++;
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
    reg->ip++;
}
int execMoveToR8(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveToR8\n");
    }
    reg->ip++;
}
int execMoveFromSegment(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveFromSegment\n");
    }
    reg->ip++;
}
int execMoveToSegment(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveToSegment\n");
    }
    reg->ip++;
}
int execMoveAH(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveAH\n");
    }
    reg->ip++;
}
int execMoveAX(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveAX\n");
    }
    reg->ip++;
}
int execMoveDX(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveDX\n");
    }
    reg->ip++;
}
int execMoveBX(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveBX\n");
    }
    reg->ip++;
}
int execMoveSI(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveSI\n");
    }
    reg->ip++;
}
int execMoveDI(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveDI\n");
    }
    reg->ip++;
}
int execMoveIMM16toRM16(byte *memory,registers* reg){
    if(LOGGER){
        printf("MoveIMM16toRM16\n");
    }
    reg->ip++;
}
int execInterrupt(byte *memory,registers* reg){
    if(LOGGER){
        printf("Interrupt\n");
    }
    reg->ip++;
}
int execJump(byte *memory,registers* reg){
    if(LOGGER){
        printf("Jump\n");
    }
    reg->ip++;
}
int execIncrement(byte *memory,registers* reg){
    if(LOGGER){
        printf("Increment\n");
    }
    reg->ip++;
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