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

#define LOGGER 0
#define displayPointer /*0xA000*/ 0xB800
#define codeOffset 0x100

void execAddR8toRM8(byte *memory,registers* reg);
void execAdd(byte *memory,registers* reg);
void execXor(byte *memory,registers* reg);
void execIncrementEDX(byte *memory,registers* reg);
void execIncrementEBX(byte *memory,registers* reg);
void execDecrementECX(byte *memory,registers* reg);
void execJumpNotEqual(byte *memory,registers* reg);
void execJumpNotParity(byte *memory,registers* reg);
void execCompare(byte *memory,registers* reg);
void execMoveToR8(byte *memory,registers* reg);
void execMoveFromSegment(byte *memory,registers* reg);
void execMoveToSegment(byte *memory,registers* reg);
void execMoveAH(byte *memory,registers* reg);
void execMoveAX(byte *memory,registers* reg);
void execMoveDX(byte *memory,registers* reg);
void execMoveBX(byte *memory,registers* reg);
void execMoveSI(byte *memory,registers* reg);
void execMoveDI(byte *memory,registers* reg);
void execMoveIMM16toRM16(byte *memory,registers* reg);
int execInterrupt(byte *memory,registers* reg);
void execJump(byte *memory,registers* reg);
void execIncrement(byte *memory,registers* reg);



void printMemory(byte* memory, int memSize);
void printByte(byte b);

int getRMField(byte addrMode);
int getAdressingMode(byte addrMode);
int getModifier(byte addrMode);

halfRegister* getRegister(int correctPartOfAddrMode, registers* reg);
halfRegister* getSegment(int correctPartOfAddrMode, registers* reg);
#endif