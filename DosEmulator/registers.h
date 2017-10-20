#include <stdint.h>
#ifndef registers_h
#define registers_h
typedef uint8_t byte;
typedef uint16_t halfRegister, doubleByte;
typedef uint32_t wholeRegister, quadByte;

typedef struct {
    union {
        struct{byte al;byte ah;};
        halfRegister ax;
        wholeRegister eax;
    };
    union {
        struct{byte bl;byte bh;};
        halfRegister bx;
        wholeRegister ebx;
    };
    union {
        struct{byte cl;byte ch;};
        halfRegister cx;
        wholeRegister ecx;
    };
    union {
        struct{byte dl;byte dh;};
        halfRegister dx;
        wholeRegister edx;
    };
} registers;

void printRegisters(registers* reg);
void initRegisters(registers* reg);

#endif