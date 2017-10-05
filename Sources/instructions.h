#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H


// opcode instrukcí

// prefixy
#define OPSIZE 0x66
#define ADSIZE 0x67
#define ESPRF 0x26

// SIB mode 
#define SIBMODE  0x04

// opcody
#define INT				0xCD
#define MOVEAX	0xB8
#define MOVEBX	0xBB
#define MOVEDX	0xBA
#define MOVESI		0xBE
#define MOVE8C	0x8C
#define MOVE8E	0x8E
#define XOR			0x33
#define JMP			0xEB
#define INC				0xFF
#define ADD			0x03
#define MOVE8A	0x8A
#define JNP				0x7B
#define ADDADDR 0x00
#define INCEBX		0x43
#define INCEDX		0x42
#define DECECX	0x49
#define MOVEAH	0xB4
#define CMP			0x83
#define JNE				0x75
#define MOVEDI		0xBF
#define MOVEC7	0xC7

#define END			0x20

// funkce obsluhující jednotlivé instrukce

int moveEax(REG *regs, byte *memory);
int move8C(REG *regs, byte *memory);
int move8E(REG *regs, byte *memory);
int xor_instr(REG *regs, byte *memory);
int moveEdx(REG *regs, byte *memory);
int moveEsi(REG *regs, byte *memory);
int moveEbx(REG *regs, byte *memory);
int jmp(REG *regs, byte *memory);
int inc(REG *regs, byte *memory);
int add(REG *regs, byte *memory);
int move8A(REG *regs, byte *memory);
int incebx(REG *regs, byte *memory);
int incedx(REG *regs, byte *memory);
int dececx(REG *regs, byte *memory);
int moveah(REG *regs, byte *memory);
int addaddr(REG *regs, byte *memory);
int movedi(REG *regs, byte *memory);
int movec7(REG *regs, byte *memory);

#endif 