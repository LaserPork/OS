#include "registers.h"
#ifndef memory_h
#define memory_h

/* prefixy */
#define segmentOverride 0x26
#define operandOverride 0x66
#define addressOverride 0x67

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

#define LOGGER 1

int execAddR8toRM8(byte *memory,registers* reg);
int execAdd(byte *memory,registers* reg);
int execXor(byte *memory,registers* reg);
int execIncrementEDX(byte *memory,registers* reg);
int execIncrementEBX(byte *memory,registers* reg);
int execDecrementECX(byte *memory,registers* reg);
int execJumpNotEqual(byte *memory,registers* reg);
int execJumpNotParity(byte *memory,registers* reg);
int execCompare(byte *memory,registers* reg);
int execMoveToR8(byte *memory,registers* reg);
int execMoveFromSegment(byte *memory,registers* reg);
int execMoveToSegment(byte *memory,registers* reg);
int execMoveAH(byte *memory,registers* reg);
int execMoveAX(byte *memory,registers* reg);
int execMoveDX(byte *memory,registers* reg);
int execMoveBX(byte *memory,registers* reg);
int execMoveSI(byte *memory,registers* reg);
int execMoveDI(byte *memory,registers* reg);
int execMoveIMM16toRM16(byte *memory,registers* reg);
int execInterrupt(byte *memory,registers* reg);
int execJump(byte *memory,registers* reg);
int execIncrement(byte *memory,registers* reg);



void printMemory(byte* memory, int memSize);


#endif