#include <stdio.h>
#include <malloc.h>
#include "registers.h"
#include "memory.h"
#include <math.h>
#include <stdlib.h>
#include <process.h>


register_fce *inicializing_register_functions(void) {

	static register_fce registers_array[256];
	
	registers_array[0] = execAddR8toRM8;
	registers_array[3] = execAdd;
	registers_array[51] = execXor;
	registers_array[66] = execIncrementEDX;
	registers_array[67] = execIncrementEBX;
	registers_array[73] = execDecrementECX;
	registers_array[117] = execJumpNotEqual;
	registers_array[123] = execJumpNotParity;
	registers_array[131] = execCompare;
	registers_array[138] = execMoveToR8;
	registers_array[140] = execMoveFromSegment;
	registers_array[142] = execMoveToSegment ;
	registers_array[180] =execMoveAH;
	registers_array[184] = execMoveAX;
	registers_array[186] = execMoveDX;
	registers_array[187] = execMoveBX;
	registers_array[190] = execMoveSI;
	registers_array[191] = execMoveDI;
	registers_array[199] = execMoveIMM16toRM16;
	registers_array[205] = execInterrupt;
	registers_array[235] = execJump;
	registers_array[255] = execIncrement;

	return registers_array;
}

int executeInstructions(registers* dosRegisters, byte *memory) {
	int returnValue = 0;
	register_fce *functions;
	functions = inicializing_register_functions();

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
	fopen_s(&filePointer,filename, "rb");

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

	
	return -2;


}


int main() {
	registers *dosRegisters;
	byte *memory;
	dosRegisters = malloc(sizeof(registers));
	memory = malloc((int)pow(2, 16) * sizeof(byte));
	initRegisters(dosRegisters);
	loadFileintoMemory(memory);
	executeInstructions(dosRegisters, memory);
	return 0;
}