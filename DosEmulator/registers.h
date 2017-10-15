#include <stdint.h>
#ifndef registers_h
#define registers_h
typedef uint8_t quarterRegister;
typedef uint16_t halfRegister;
typedef uint32_t wholeRegister;

typedef struct {
    union {
        struct{quarterRegister al;quarterRegister ah;};
        halfRegister ax;
        wholeRegister eax;
    };
    union {
        struct{quarterRegister bl;quarterRegister bh;};
        halfRegister bx;
        wholeRegister ebx;
    };
    union {
        struct{quarterRegister cl;quarterRegister ch;};
        halfRegister cx;
        wholeRegister ecx;
    };
    union {
        struct{quarterRegister dl;quarterRegister dh;};
        halfRegister dx;
        wholeRegister edx;
    };
} registers;

void printRegisters(registers* reg);
void initRegisters(registers* reg);

#endif