#include "registers.h"
#include "memory.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


int exec_add_R8_to_RM8(byte *memory, regs_and_flags *reg) {
	half_register *destinationRegister, *sourceRegister;
	if (LOGGER) {
		printf("AddR8toRM8\n");
	}
	reg->ip++;
	destinationRegister = get_register(get_rm_field(memory[reg->ip]), reg);
	sourceRegister = get_register(get_modifier(memory[reg->ip]), reg);
	if (LOGGER) {
		printf("->Memory[%02X] is set to %02X + %02X\n", *destinationRegister, memory[*destinationRegister], *sourceRegister);
	}
	memory[*destinationRegister] = (byte)(memory[*destinationRegister] + *sourceRegister);
	if (LOGGER) {
		printf("-->Memory[%02X] is now %02X\n", *destinationRegister, memory[*destinationRegister]);
	}
	reg->ip++;
	
	return 0;
}
int exec_add(byte *memory, regs_and_flags *reg) {
	half_register *destinationRegister, *sourceRegister;
	if (LOGGER) {
		printf("Add\n");
	}
	reg->ip += 1;
	/*
	destinationRegister = getRegister(get_rm_field(memory[reg->ip]),reg);
	sourceRegister = get_register(get_modifier(memory[reg->ip]),reg);
	*/
	destinationRegister = get_register(get_modifier(memory[reg->ip]), reg);
	sourceRegister = get_register(get_rm_field(memory[reg->ip]), reg);
	if (LOGGER) {
		printf("->Value %02X was added to register with value %02X\n", *sourceRegister, *destinationRegister);
	}
	*destinationRegister = *sourceRegister + *destinationRegister;
	reg->ip += 1;
	return 0;
}
int exec_xor(byte *memory, regs_and_flags *reg) {
	whole_register *destination_register, *source_register;
	if (LOGGER) {
		printf("Xor\n");
	}
	if (reg->operand_override) {
		reg->operand_override = 0;
		reg->ip += 1;
		destination_register = (whole_register*) get_register(get_rm_field(memory[reg->ip]), reg);
		source_register = (whole_register*) get_register(get_modifier(memory[reg->ip]), reg);
		*destination_register = *source_register ^ *destination_register;
		reg->ip += 1;
	}
	else {
		printf("Xor without operand override index was not implemented");
		exit(-1);
	}

	return 0;
}
int exec_increment_EDX(byte *memory, regs_and_flags *reg) {
	if (LOGGER) {
		printf("IncrementEDX\n");
	}
	if (reg->operand_override) {
		reg->operand_override = 0;
		reg->edx = reg->edx + 1;
	}
	else {
		printf("Increment EDX without prefix was not implemented");
		exit(-1);
	}

	reg->ip++;
	return 0;
}
int exec_increment_EBX(byte *memory, regs_and_flags *reg) {
	if (LOGGER) {
		printf("IncrementEBX\n");
	}
	if (reg->operand_override) {
		reg->operand_override = 0;
		reg->ebx = reg->ebx + 1;
	}
	else {
		printf("Increment EBX without prefix was not implemented");
		exit(-1);
	}
	reg->ip++;
	return 0;
}
int exec_decrement_ECX(byte *memory, regs_and_flags *reg) {
	if (LOGGER) {
		printf("DecrementECX\n");
	}
	if (reg->operand_override) {
		reg->operand_override = 0;
		reg->ecx = reg->ecx - 1;
	}
	else {
		reg->cx -= 1;
	}
	reg->ip++;
	return 0;
}
int exec_jump_not_equal(byte *memory, regs_and_flags *reg) {
	if (LOGGER) {
		printf("JumpNotEqual\n");
	}
	reg->ip++;
	int8_t i = (byte)memory[reg->ip];
	/*printf("Skok je %d\n",i);*/
	if (reg->is_equal) {
		reg->ip++;
	}
	else {
		reg->ip += i;
		reg->ip++;
	}
	return 0;
}
int exec_jump_not_parity(byte *memory, regs_and_flags *reg) {
	if (LOGGER) {
		printf("JumpNotParity\n");
	}
	reg->ip++;
	return 0;
}
int exec_compare(byte *memory, regs_and_flags *reg) {
	half_register *destination_register;
	if (LOGGER) {
		printf("Compare\n");
	}
	reg->ip++;
	destination_register = get_register(get_rm_field(memory[reg->ip]), reg);
	if (*destination_register == (int8_t)memory[reg->ip + 1]) {
		if (LOGGER) {
			printf("%d is equal to %d\n", *destination_register, memory[reg->ip + 1]);
		}
		reg->is_equal = 1;
	}
	else {
		if (LOGGER) {
			printf("%d is not equal to %d\n", *destination_register, memory[reg->ip + 1]);
		}
		reg->is_equal = 0;
	}
	reg->ip += 2;
	return 0;
}
int exec_move_to_R8(byte *memory, regs_and_flags *reg) {
	half_register *destination_register, address_in_memory, *other_register;
	if (LOGGER) {
		printf("MoveToR8\n");
	}
	reg->ip++;
	if (get_adressing_mode(memory[reg->ip]) == 0) {
		destination_register = get_register(get_modifier(memory[reg->ip]), reg);
		other_register = get_register(get_rm_field(memory[reg->ip]), reg);
		address_in_memory = 0;
		if (!(reg->operand_override || reg->segment_override || reg->address_override)) {
			address_in_memory = (half_register)(memory[reg->ip + 1] + memory[reg->ip + 2] * 0x100);
			reg->ip += 3;
		}
		else if (reg->address_override) {
			reg->address_override = 0;
			if (other_register == &reg->sp) { /* SIB */
											 /* 43  mov al, byte ptr es:[esi+eax] */
				if (memory[reg->ip + 1] == 0x06) {
					address_in_memory = reg->ax + reg->si;
					reg->ip += 2;
				}
				else {
					printf("Unimplemeted SIB mode for move_to_R8\n");
					exit(-1);
				}

			}
			else {

				/* 42  mov al, byte ptr ds:[edx]*/
				address_in_memory = *other_register;
				reg->ip++;
			}
		}

		if (reg->segment_override) {
			reg->segment_override = 0;
			address_in_memory += reg->es;
		}
		else {
			address_in_memory += reg->ds;
		}
		*destination_register = memory[address_in_memory];
	}
	else {
		printf("Unimplemented Addressing mode\n");
		exit(-1);
	}

	return 0;
	/* muze byt jine*/
}
int exec_move_from_segment(byte *memory, regs_and_flags *reg) {
	half_register *destination_register, *segment_register;
	if (LOGGER) {
		printf("MoveFromSegment\n");
	}
	reg->ip += 1;
	if (get_adressing_mode(memory[reg->ip]) == 3) {
		destination_register = get_register(get_rm_field(memory[reg->ip]), reg);
		segment_register = get_segment(get_modifier(memory[reg->ip]), reg);
		*destination_register = *segment_register;
	}
	else {
		printf("Unimplemented Addressing mode\n");
		exit(-1);
	}
	reg->ip += 1;
	return 0;
}
int exec_move_to_segment(byte *memory, regs_and_flags *reg) {
	half_register *source_register, *segment_register;
	if (LOGGER) {
		printf("MoveToSegment\n");
	}
	reg->ip += 1;
	if (get_adressing_mode(memory[reg->ip]) == 3) {
		source_register = get_register(get_rm_field(memory[reg->ip]), reg);
		segment_register = get_segment(get_modifier(memory[reg->ip]), reg);
		*segment_register = *source_register;
	}
	else {
		printf("Unimplemented Addressing mode\n");
		exit(-1);
	}
	reg->ip += 1;
	return 0;
}
int exec_move_AH(byte *memory, regs_and_flags *reg) {
	if (LOGGER) {
		printf("MoveAH\n");
	}
	reg->ip++;
	reg->ah = memory[reg->ip];
	reg->ip++;
	return 0;
}
int exec_move_AX(byte *memory, regs_and_flags *reg) {
	if (LOGGER) {
		printf("MoveAX\n");
	}
	reg->ip++;
	reg->ax = memory[reg->ip++];
	reg->ax += memory[reg->ip++] * 0x100;
	return 0;
}
int exec_move_DX(byte *memory, regs_and_flags *reg) {
	if (LOGGER) {
		printf("MoveDX\n");
	}
	reg->ip++;
	reg->dx = memory[reg->ip++];
	reg->dx += memory[reg->ip++] * 0x100;
	return 0;
}
int exec_move_BX(byte *memory, regs_and_flags *reg) {
	if (LOGGER) {
		printf("MoveBX\n");
	}
	reg->ip++;
	reg->bx = memory[reg->ip++];
	reg->bx += memory[reg->ip++] * 0x100;
	return 0;
}
int exec_move_SI(byte *memory, regs_and_flags *reg) {
	if (LOGGER) {
		printf("MoveSI\n");
	}
	reg->ip++;
	reg->si = memory[reg->ip++];
	reg->si += memory[reg->ip++] * 0x100;
	return 0;
}
int exec_move_DI(byte *memory, regs_and_flags *reg) {
	if (LOGGER) {
		printf("MoveDI\n");
	}
	reg->ip++;
	reg->di = memory[reg->ip++];
	reg->di += memory[reg->ip++] * 0x100;
	return 0;
}
int exec_move_IMM16_to_RM16(byte *memory, regs_and_flags *reg) {
	half_register *destination_register, address_in_memory;
	byte  value1, value2;
	if (LOGGER) {
		printf("MoveIMM16toRM16\n");
	}
	reg->ip++;
	if (get_adressing_mode(memory[reg->ip]) == 2) {
		destination_register = get_register(get_rm_field(memory[reg->ip]), reg);
		address_in_memory = (half_register)(reg->ds + *destination_register + memory[reg->ip + 1] + memory[reg->ip + 2] * 0x100);
		value1 = memory[reg->ip + 3];
		value2 = memory[reg->ip + 4];
		memory[address_in_memory] = value1;
		memory[address_in_memory + 1] = value2;
		reg->ip += 5;
	}
	else {
		printf("Unimplemeted Addressing mode when writing to memory\n");
	}
	return 0;
}
int exec_interrupt(byte *memory, regs_and_flags *reg) {
	reg->ip++;
	if (LOGGER) {
		printf("Interrupt\n");
	}

	if (memory[reg->ip] == 0x10) {
		if (LOGGER) {
			printf("->Setting screen mode\n");
		}
	memset(memory + display_pointer, 0, 80 * 25 * 2);
	
		system("MODE CON: COLS=80 LINES=25\n");

		reg->ip++;
		return 10;
	}
	else if (memory[reg->ip] == 0x20) {
		system("color\n");
		if (LOGGER) {
			printf("->Quitting\n");
		}
		int i;
		byte ch, color;
		for (i = 0; i< 80 * 2; i++) {
			//   if(i%80 == 0 && i != 0){printf("\n");continue;};
			color = memory[display_pointer + i * 2 + 1];

			ch = memory[display_pointer + i * 2];
			if (ch>0x20 && ch<0xff && color == 0) {
				printf("%c", ch);
			}
			else if (ch>0x20 && ch<0xff && color == 0x79) {
				printf("\x1b[34;1m");
				printf("\x1b[47m");
				printf("%c", ch);
				printf("\x1b[0m");
			}
			else {
				printf(" ");
			}


		}
		reg->ip++;
		return 20;
	}
	else if (memory[reg->ip] == 0x21) {
		int i;
		half_register address_in_memory;
		byte ch;
		if (LOGGER) {
			printf("->Writing into graphic buffer\n");
		}
		for (i = 0; i< 80 * 25 * 2; i++) {
			address_in_memory = (half_register)(reg->dx + i);
			ch = memory[address_in_memory];
			if (ch == 0x24) {
				break;
			}
			memory[display_pointer + 2 * i] = ch;
		}
		reg->ip++;
		return 21;
	}
	else {
		return -1;
	}
}
int exec_jump(byte *memory, regs_and_flags *reg) {
	if (LOGGER) {
		printf("Jump\n");
	}
	reg->ip++;
	int8_t i = (byte)memory[reg->ip];
	//printf("Skok je %d\n",i);
	reg->ip += i;
	reg->ip++;
	/*tady je ten podelany skok o -1, ma sezrat 2 byty ale vysledne jen sebe*/
	return 0;
}
int exec_increment(byte *memory, regs_and_flags *reg) {
	whole_register * destination_register;
	if (LOGGER) {
		printf("Increment\n");
	}
	reg->ip++;
	destination_register = (whole_register*) get_register(get_rm_field(memory[reg->ip]), reg);
	*destination_register = *destination_register + 1;
	reg->ip++;
	return 0;
}

void print_memory(byte *memory, int memSize) {
	int i;
	printf("MEMORY DUMP: %d bytes\n", memSize);
	for (i = code_offset; i < (code_offset + memSize); i++) {
		printf("%02X", memory[i]);
	}
	printf("\n");
}

void print_byte(byte b) {
	int i;

	printf("%02X\n", b);

	for (i = 0; i<8; i++) {
		printf("%i", b & 0x01);
		b = b >> 1;
		if (i == 2) {
			printf(" ");
		}
		if (i == 5) {
			printf(" ");
		}
	}
	printf("\n");

}

int get_rm_field(byte addr_mode) {  /*first lower*/
	return addr_mode & 7;
}

int get_adressing_mode(byte addr_mode) { /*second middle*/
	return addr_mode >> 6;
}

int get_modifier(byte addr_mode) {
	return (addr_mode >> 3) & 7;
}

half_register* get_register(int correct_part_of_addr_mode, regs_and_flags *reg) {
	switch (correct_part_of_addr_mode)
	{
	case 0: return &reg->ax;
	case 1: return &reg->cx;
	case 2: return &reg->dx;
	case 3: return &reg->bx;
	case 4: return &reg->sp;
	case 5: return &reg->bp;
	case 6: return &reg->si;
	case 7: return &reg->bx; /*to tady je protoze kdyz ho chci tak jsem v 16 bit modu*/
	default:
		printf("Unknown destination register\n");
		exit(-1);
	}

}

half_register* get_segment(int correct_part_of_addr_mode, regs_and_flags *reg) {
	switch (correct_part_of_addr_mode)
	{
	case 0: return &reg->es;
	case 1: return &reg->cs;
	case 3: return &reg->ds;
	default:
		printf("Unknown segment register\n");
		exit(-1);
	}
}