#ifndef CPU_H
#define CPU_H

#define DEBUG_MODE 1							// prezentační mód
#define REG_COUNT 16							// počet dostuponých registrů
#define HEADER_SIZE 0x100 					// velikost hlavicky v pameni ptogramu
#define SEGMENT_SIZE 65536				// velikost rezervované paměti
#define INTERRUPTS_COUNT 256		// velikost tabulky přerušení;

#define DISPLAY_POINTER	0xB800		// pointer do paměti pro uložení výstupu na display
#define STRING 0x24								// terminální znak výpisu řetězce (pro int 21h)
// pomocné rutiny

void printReg(REG *regs);
char doplnek(char value);
reg16 *getRMregister(byte position, byte val, REG *regs);
reg16 *getRMsegment(byte position, byte val, REG *regs);
byte getRMmode(byte val);

// obsluha přerušení

int int_10(REG *regs, byte *memory);
int int_20(REG *regs, byte *memory);
int int_21(REG *regs, byte *memory);

void writeBuffer(byte *memory);



#endif 
