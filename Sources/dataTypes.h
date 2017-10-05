#ifndef DATATYPES_H
#define DATATYPES_H

typedef unsigned long  reg32;
typedef unsigned int  reg16;
typedef unsigned char byte;

// struktura pro uložení regsitrů

typedef struct
{
	union					// AX
	{
		reg16 ax;
		reg32 eax;
		struct
		{
			byte al;
			byte ah;
		};
	};
	
	union					// BX
	{
		reg16 bx;
		reg32 ebx;
		struct
		{
			byte bl;
			byte bh;
		};
	};
	
		union				// CX
	{
		reg16 cx;
		reg32 ecx;
		struct
		{
			byte cl;
			byte ch;
		};
	};
	
	union					// DX
	{
		reg16 dx;
		reg32 edx;
		struct
		{
			byte dl;
			byte dh;
		};
	};
	
	reg16 si;
	reg16 di;
	
	reg16 cs;
	reg16 ds;
	reg16 es;
	reg16 ss;
	
	reg16 sp;
	reg16 bp;
	
	reg16 ip;
	
	byte flag;
	byte prefix;		// pseudoregistr pro uložení prefixu instrukce 0x66 nebo 0x67
	byte espref;		// pseudoregistr pro uložení prefixu instrukce říkající, že má použít ES míst DS
	byte equal;		// pseudoregistr pro uložení výsledku porovnání. Následně se bere v úvahu v podmíněném skoku
} REG;

#endif 