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
        if(memory[dosRegisters->ip] == segmentOverrideValue ||
           memory[dosRegisters->ip] == operandOverrideValue ||
           memory[dosRegisters->ip] == addressOverrideValue){
            switch(memory[dosRegisters->ip]){
                case segmentOverrideValue: dosRegisters->segmentOverride=1;break;
                case operandOverrideValue: dosRegisters->operandOverride=1;break;
                case addressOverrideValue: dosRegisters->addressOverride=1;break;
                default: break;
            }
            dosRegisters->ip++;
        }else {
            switch (memory[dosRegisters->ip]) {
                case addR8toRM8:
                    execAddR8toRM8(memory, dosRegisters);
                    break;
                case add:
                    execAdd(memory, dosRegisters);
                    break;
                case xor:
                    execXor(memory, dosRegisters);
                    break;
                case incrementEDX:
                    execIncrementEDX(memory, dosRegisters);
                    break;
                case incrementEBX:
                    execIncrementEBX(memory, dosRegisters);
                    break;
                case decrementECX:
                    execDecrementECX(memory, dosRegisters);
                    break;
                case jumpNotEqual:
                    execJumpNotEqual(memory, dosRegisters);
                    break;
                case jumpNotParity:
                    execJumpNotParity(memory, dosRegisters);
                    break;
                case compare:
                    execCompare(memory, dosRegisters);
                    break;
                case moveToR8:
                    execMoveToR8(memory, dosRegisters);
                    break;
                case moveFromSegment:
                    execMoveFromSegment(memory, dosRegisters);
                    break;
                case moveToSegment:
                    execMoveToSegment(memory, dosRegisters);
                    break;
                case moveAH:
                    execMoveAH(memory, dosRegisters);
                    break;
                case moveAX:
                    execMoveAX(memory, dosRegisters);
                    break;
                case moveDX:
                    execMoveDX(memory, dosRegisters);
                    break;
                case moveBX:
                    execMoveBX(memory, dosRegisters);
                    break;
                case moveSI:
                    execMoveSI(memory, dosRegisters);
                    break;
                case moveDI:
                    execMoveDI(memory, dosRegisters);
                    break;
                case moveIMM16toRM16:
                    execMoveIMM16toRM16(memory, dosRegisters);
                    break;
                case interrupt:
                    returnValue = execInterrupt(memory, dosRegisters);
                    break;
                case jump:
                    execJump(memory, dosRegisters);
                    break;
                case increment:
                    execIncrement(memory, dosRegisters);
                    break;
                default:
                    printf("Opcode %02x is not implemeted\n", memory[dosRegisters->ip]);
                    exit(-1);
            }
            if(dosRegisters->operandOverride || dosRegisters->segmentOverride || dosRegisters->addressOverride){
                printf("Instruction did not consume prefix correctly\n");
                exit(-1);
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