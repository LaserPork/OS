#include <stdint.h>
#ifndef registers_h
#define registers_h
typedef uint8_t byte;
typedef uint16_t halfRegister, doubleByte;
typedef uint32_t wholeRegister, quadByte;



typedef struct {
	//GENERAL REGISTERS --- celych 32 bitu snad nikndy nebudeme potrebovat -> pouyivat jen AX ne EAX
	union {
		struct { byte al; byte ah; };
		halfRegister ax;
		wholeRegister eax;
	};
	union {
		struct { byte bl; byte bh; };
		halfRegister bx;
		wholeRegister ebx;
	};
	union {
		struct { byte cl; byte ch; };
		halfRegister cx;
		wholeRegister ecx;
	};
	union {
		struct { byte dl; byte dh; };
		halfRegister dx;
		wholeRegister edx;
	};
	//SEGMENT REGISTERS
	halfRegister cs; //code segment
	halfRegister ds; //data segment
	halfRegister ss; //stack segment
	halfRegister es; //extra segment
					 //INDEX REGISTERS
	halfRegister di; //destination index
	halfRegister si; //stack index snad nebudeme zasobnik potrebovat
					 //POINTERS
	halfRegister sp; //stack pointer snad nebudeme zasobnik potrebovat
	halfRegister bp; //base pointer
	halfRegister ip; //instruciton pointer

	int segmentOverride;
	int operandOverride;
	int addressOverride;
	int isEqual;
} regs_and_flags;


void printRegisters(regs_and_flags* reg);
void initRegisters(regs_and_flags* reg);

#endif