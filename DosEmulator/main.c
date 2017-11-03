#include <stdio.h>
#include <malloc.h>
#include "registers.h"
#include "memory.h"
#include <math.h>


int executeInstructions(registers* dosRegisters, byte *memory){
    int returnValue = 0;
    while(1){
        if(LOGGER){
            printf("Opcode: %02x \n", memory[dosRegisters->ip]);
        }
        if(memory[dosRegisters->ip ] == segmentOverride || memory[dosRegisters->ip ] ==  operandOverride || memory[dosRegisters->ip ] == addressOverride){
            dosRegisters->ip++;
        }else {
            switch (memory[dosRegisters->ip]) {
                case addR8toRM8:
                    returnValue = execAddR8toRM8(memory, dosRegisters);
                    break;
                case add:
                    returnValue = execAdd(memory, dosRegisters);
                    break;
                case xor:
                    returnValue = execXor(memory, dosRegisters);
                    break;
                case incrementEDX:
                    returnValue = execIncrementEDX(memory, dosRegisters);
                    break;
                case incrementEBX:
                    returnValue = execIncrementEBX(memory, dosRegisters);
                    break;
                case decrementECX:
                    returnValue = execDecrementECX(memory, dosRegisters);
                    break;
                case jumpNotEqual:
                    returnValue = execJumpNotEqual(memory, dosRegisters);
                    break;
                case jumpNotParity:
                    returnValue = execJumpNotParity(memory, dosRegisters);
                    break;
                case compare:
                    returnValue = execCompare(memory, dosRegisters);
                    break;
                case moveToR8:
                    returnValue = execMoveToR8(memory, dosRegisters);
                    break;
                case moveFromSegment:
                    returnValue = execMoveFromSegment(memory, dosRegisters);
                    break;
                case moveToSegment:
                    returnValue = execMoveToSegment(memory, dosRegisters);
                    break;
                case moveAH:
                    returnValue = execMoveAH(memory, dosRegisters);
                    break;
                case moveAX:
                    returnValue = execMoveAX(memory, dosRegisters);
                    break;
                case moveDX:
                    returnValue = execMoveDX(memory, dosRegisters);
                    break;
                case moveBX:
                    returnValue = execMoveBX(memory, dosRegisters);
                    break;
                case moveSI:
                    returnValue = execMoveSI(memory, dosRegisters);
                    break;
                case moveDI:
                    returnValue = execMoveDI(memory, dosRegisters);
                    break;
                case moveIMM16toRM16:
                    returnValue = execMoveIMM16toRM16(memory, dosRegisters);
                    break;
                case interrupt:
                    returnValue = execInterrupt(memory, dosRegisters);
                    break;
                case jump:
                    returnValue = execJump(memory, dosRegisters);
                    break;
                case increment:
                    returnValue = execIncrement(memory, dosRegisters);
                    break;
                default:
                    printf("This virtualization doesn't use opcode %02x \n", memory[dosRegisters->ip]);
                    dosRegisters->ip++;
                    break;
            }
            if(returnValue == 20){
                return 0;
            }

        }
    }
}
int loadFileintoMemory(byte *memory){
    FILE *filePointer;
    char *filename = "VB08.COM";
    filePointer = fopen(filename,"rb");

    int c,memSize = 0;

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
        memory[0x100+memSize++] = (byte) c;
    }
    printMemory(memory, memSize);
}


int main() {
    registers *dosRegisters;
    byte *memory;
    dosRegisters = malloc(sizeof(registers));
    memory = malloc((int)pow(2,16) * sizeof(byte));
    initRegisters(dosRegisters);
    loadFileintoMemory(memory);
    executeInstructions(dosRegisters, memory);
    return 0;
}