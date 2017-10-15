#include <stdio.h>
#include "registers.h"


int main() {
    registers dosRegisters;
    initRegisters(&dosRegisters);
    printRegisters(&dosRegisters);
    return 0;
}