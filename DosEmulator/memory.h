#include "registers.h"
#ifndef memory_h
#define memory_h

/* prefixy */
#define segmentOverride 0x26
#define operandOverride 0x66
#define addressOverride 0x67

/* instrukce */
#define addR8toR/M8 0x00
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
#define moveIMM16toR/M16 0xC7
#define interrupt 0xCD
#define jump0xEB
#define increment 0xFF

void printMemory(byte* memory, int memSize);


#endif