#include "registers.h"
#ifndef memory_h
#define memory_h

/* prefixy */
#define segmentOverrideValue 0x26
#define operandOverrideValue 0x66
#define addressOverrideValue 0x67

/* instrukce */
#define addR8toRM8 0x00
#define add 0x03
#define xor 0x33
#define incrementEDX 0x42
#define incrementEBX 0x43
#define decrementECX 0x49
#define jumpNotEqual 0x75
#define jumpNotParity 0x7B
#define compare 0x83
#define moveToR8 0x8A
#define moveFromSegment 0x8C
#define moveToSegment 0x8E
#define moveAH 0xB4
#define moveAX 0xB8
#define moveDX 0xBA
#define moveBX 0xBB
#define moveSI 0xBE
#define moveDI 0xBF
#define moveIMM16toRM16 0xC7
#define interrupt 0xCD
#define jump 0xEB
#define increment 0xFF

#define opcode_count 0x100

#define LOGGER 0
#define displayPointer /*0xA000*/ 0xB800
#define codeOffset 0x100

int execAddR8toRM8(byte *memory, regs_and_flags* reg);
int execAdd(byte *memory, regs_and_flags* reg);
int execXor(byte *memory, regs_and_flags* reg);
int execIncrementEDX(byte *memory, regs_and_flags* reg);
int execIncrementEBX(byte *memory, regs_and_flags* reg);
int execDecrementECX(byte *memory, regs_and_flags* reg);
int execJumpNotEqual(byte *memory, regs_and_flags* reg);
int execJumpNotParity(byte *memory, regs_and_flags* reg);
int execCompare(byte *memory, regs_and_flags* reg);
int execMoveToR8(byte *memory, regs_and_flags* reg);
int execMoveFromSegment(byte *memory, regs_and_flags* reg);
int execMoveToSegment(byte *memory, regs_and_flags* reg);
int execMoveAH(byte *memory, regs_and_flags* reg);
int execMoveAX(byte *memory, regs_and_flags* reg);
int execMoveDX(byte *memory, regs_and_flags* reg);
int execMoveBX(byte *memory, regs_and_flags* reg);
int execMoveSI(byte *memory, regs_and_flags* reg);
int execMoveDI(byte *memory, regs_and_flags* reg);
int execMoveIMM16toRM16(byte *memory, regs_and_flags* reg);
int execInterrupt(byte *memory, regs_and_flags* reg);
int execJump(byte *memory, regs_and_flags* reg);
int execIncrement(byte *memory, regs_and_flags* reg);



void printMemory(byte* memory, int memSize);
void printByte(byte b);

int getRMField(byte addrMode);
int getAdressingMode(byte addrMode);
int getModifier(byte addrMode);

halfRegister* getRegister(int correctPartOfAddrMode, regs_and_flags* reg);
halfRegister* getSegment(int correctPartOfAddrMode, regs_and_flags* reg);
#endif