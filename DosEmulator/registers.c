#include <stdio.h>
#include "registers.h"
#include "memory.h"

void print_registers(regs_and_flags *reg) {
	printf("  [    E_X    ]\n");
	printf("  [ _X ]       \n");
	printf("  L  H         \n");
	int i = 0;
	while (i < sizeof(whole_register) * 4)
	{
		if (i % 2 == 0) {
			printf("  ");
		}
		printf("%02X ", *((byte *)reg + i));
		i++;
		if (i % 4 == 0) {
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

void init_registers(regs_and_flags *reg) {
	reg->eax = 0x00000000;
	reg->ebx = 0x00000000;
	reg->ecx = 0x00000000;
	reg->edx = 0x00000000;
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
	reg->ip = code_offset;
	reg->operand_override = 0;
	reg->address_override = 0;
	reg->segment_override = 0;
}