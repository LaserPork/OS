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
	functions[add_R8_to_RM8] = exec_add_R8_to_RM8;
	functions[add] = exec_add;
	functions[xor] = exec_xor;
	functions[increment_EDX] = exec_increment_EDX;
	functions[increment_EBX] = exec_increment_EBX;
	functions[decrement_ECX] = exec_decrement_ECX;
	functions[jump_not_equal] = exec_jump_not_equal;
	functions[jump_not_parity] = exec_jump_not_parity;
	functions[compare] = exec_compare;
	functions[move_to_R8] = exec_move_to_R8;
	functions[move_from_segment] = exec_move_from_segment;
	functions[move_to_segment] = exec_move_to_segment ;
	functions[move_AH] = exec_move_AH;
	functions[move_AX] = exec_move_AX;
	functions[move_DX] = exec_move_DX;
	functions[move_BX] = exec_move_BX;
	functions[move_SI] = exec_move_SI;
	functions[move_DI] = exec_move_DI;
	functions[move_IMM16_to_RM16] = exec_move_IMM16_to_RM16;
	functions[interrupt] = exec_interrupt;
	functions[jump] = exec_jump;
	functions[increment] = exec_increment;
}

int execute_instructions(regs_and_flags *dos_registers, byte *memory) {
	int return_value = 0;
    int(*functions[opcode_count]) (byte *, regs_and_flags*);
	inicializing_functions(functions);
	while (1) {
		if (LOGGER) {
			printf("Opcode: %02x \n", memory[dos_registers->ip]);
		}
		if (memory[dos_registers->ip] == segment_override_value ||
			memory[dos_registers->ip] == operand_override_value ||
			memory[dos_registers->ip] == address_override_value) {
			switch (memory[dos_registers->ip]) {
                case segment_override_value: dos_registers->segment_override = 1; break;
                case operand_override_value: dos_registers->operand_override = 1; break;
                case address_override_value: dos_registers->address_override = 1; break;
                default: break;
			}
			dos_registers->ip++;
		}
		else {
		    return_value = functions[(int) memory[dos_registers->ip]](memory, dos_registers);
			if (LOGGER) {
				print_registers(dos_registers);
			}
			if (dos_registers->operand_override || dos_registers->segment_override || dos_registers->address_override) {
				printf("Instruction did not consume prefix correctly\n");
				exit(-1);
			}
			if (return_value == 20) {
				return 0;
			}

		}
	}
}
int load_file_into_memory(byte *memory) {
	FILE *file_pointer;
	char *filename = "VB08.COM";
    //file_pointer = fopen(filename, "rb");
	fopen_s(&file_pointer,filename, "rb");

	int c, mem_size = 0;

	if (memory == NULL)
	{
		fprintf(stderr, "Virtual memory could not be allocated.\n");
		return(-1);
	}
	
	if (file_pointer == NULL)
	{
		printf("File could not be opened.\n");
		return -1;
	}
	
		

	while ((c = fgetc(file_pointer)) != EOF)
	{
		memory[0x100 + mem_size++] = (byte)c;
	}

	if (LOGGER) {
        print_memory(memory, mem_size);
	}

	
	return 0;


}


int main() {
	regs_and_flags *dos_registers;
	byte *memory;
	dos_registers = malloc(sizeof(regs_and_flags));
	memory = malloc((int)pow(2, 16) * sizeof(byte));
	init_registers(dos_registers);
	if(load_file_into_memory(memory)){
        free(dos_registers);
        free(memory);
        return -1;
    };
    if(execute_instructions(dos_registers, memory)){
        free(dos_registers);
        free(memory);
        return -1;
    };
	return 0;
}