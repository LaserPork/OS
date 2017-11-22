#include <stdint.h>
#ifndef registers_h
#define registers_h
typedef uint8_t byte;
typedef uint16_t half_register;
typedef uint32_t whole_register;



typedef struct {
	//GENERAL REGISTERS --- celych 32 bitu snad nikndy nebudeme potrebovat -> pouyivat jen AX ne EAX
	union {
		struct { byte al; byte ah; };
		half_register ax;
		whole_register eax;
	};
	union {
		struct { byte bl; byte bh; };
		half_register bx;
		whole_register ebx;
	};
	union {
		struct { byte cl; byte ch; };
		half_register cx;
		whole_register ecx;
	};
	union {
		struct { byte dl; byte dh; };
		half_register dx;
		whole_register edx;
	};
	//SEGMENT REGISTERS
	half_register cs; //code segment
	half_register ds; //data segment
	half_register ss; //stack segment
	half_register es; //extra segment
					 //INDEX REGISTERS
	half_register di; //destination index
	half_register si; //stack index snad nebudeme zasobnik potrebovat
					 //POINTERS
	half_register sp; //stack pointer snad nebudeme zasobnik potrebovat
	half_register bp; //base pointer
	half_register ip; //instruciton pointer

	int segment_override;
	int operand_override;
	int address_override;
	int is_equal;
} regs_and_flags;


void print_registers(regs_and_flags *reg);
void init_registers(regs_and_flags *reg);

#endif