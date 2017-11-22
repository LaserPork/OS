#include <stdio.h>
#include <malloc.h>
#include "registers.h"
#include "memory.h"
#include <math.h>
#include <stdlib.h>
#include <process.h>


void *inicializing_functions(int (*functions[opcode_count])(byte *, regs_and_flags*)) {
    int i;
    for(i = 0; i<opcode_count; i++){
        functions[i] = NULL;
    }
	functions[addR8toRM8] = execAddR8toRM8;
	functions[add] = execAdd;
	functions[xor] = execXor;
	functions[incrementEDX] = execIncrementEDX;
	functions[incrementEBX] = execIncrementEBX;
	functions[decrementECX] = execDecrementECX;
	functions[jumpNotEqual] = execJumpNotEqual;
	functions[jumpNotParity] = execJumpNotParity;
	functions[compare] = execCompare;
	functions[moveToR8] = execMoveToR8;
	functions[moveFromSegment] = execMoveFromSegment;
	functions[moveToSegment] = execMoveToSegment ;
	functions[moveAH] = execMoveAH;
	functions[moveAX] = execMoveAX;
	functions[moveDX] = execMoveDX;
	functions[moveBX] = execMoveBX;
	functions[moveSI] = execMoveSI;
	functions[moveDI] = execMoveDI;
	functions[moveIMM16toRM16] = execMoveIMM16toRM16;
	functions[interrupt] = execInterrupt;
	functions[jump] = execJump;
	functions[increment] = execIncrement;
}

int executeInstructions(regs_and_flags* dosRegisters, byte *memory) {
	int returnValue = 0;
    int(*functions[opcode_count]) (byte *, regs_and_flags*);
	inicializing_functions(functions);
	while (1) {
		if (LOGGER) {
			printf("Opcode: %02x \n", memory[dosRegisters->ip]);
		}
		if (memory[dosRegisters->ip] == segmentOverrideValue ||
			memory[dosRegisters->ip] == operandOverrideValue ||
			memory[dosRegisters->ip] == addressOverrideValue) {
			switch (memory[dosRegisters->ip]) {
                case segmentOverrideValue: dosRegisters->segmentOverride = 1; break;
                case operandOverrideValue: dosRegisters->operandOverride = 1; break;
                case addressOverrideValue: dosRegisters->addressOverride = 1; break;
                default: break;
			}
			dosRegisters->ip++;
		}
		else {
		    returnValue = functions[(int) memory[dosRegisters->ip]](memory, dosRegisters);
			if (LOGGER) {
				printRegisters(dosRegisters);
			}
			if (dosRegisters->operandOverride || dosRegisters->segmentOverride || dosRegisters->addressOverride) {
				printf("Instruction did not consume prefix correctly\n");
				exit(-1);
			}
			if (returnValue == 20) {
				return 0;
			}

		}
	}
}
int loadFileintoMemory(byte *memory) {
	FILE *filePointer;
	char *filename = "VB08.COM";
    filePointer = fopen(filename, "rb");
	//fopen_s(&filePointer,filename, "rb");

	int c, memSize = 0;

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
		memory[0x100 + memSize++] = (byte)c;
	}

	if (LOGGER) {
		printMemory(memory, memSize);
	}

	
	return 0;


}


int main() {
	regs_and_flags *dosRegisters;
	byte *memory;
	dosRegisters = malloc(sizeof(regs_and_flags));
	memory = malloc((int)pow(2, 16) * sizeof(byte));
	initRegisters(dosRegisters);
	if(loadFileintoMemory(memory)){
        free(dosRegisters);
        free(memory);
        return -1;
    };
    if(executeInstructions(dosRegisters, memory)){
        free(dosRegisters);
        free(memory);
        return -1;
    };
	return 0;
}