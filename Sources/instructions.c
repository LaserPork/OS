#include <stdio.h>
#include "dataTypes.h"
#include "tools.h"
#include "instructions.h"

// vloží hodnotu do EAX, čte zvlášt vysoký a nízký byte
int moveEax(REG *regs, byte *memory)
{	
	if (regs->prefix == 0)
	{
		regs->al = memory[regs->ip +1]; 					// nízký byte
		regs->ah =  memory[regs->ip +2]; 				// vysoký byte
		regs->ip+=3;
		
		if (DEBUG_MODE == 1)
			printf("Instrukce MOV do EAX \n");
	}
	else
	{
		printf ("MOVEAX s prefixem %d nebylo implementováno.\n", regs->prefix);
		return(-1);
	}
	return(0);
}

// Přesun v RM modu. Regostry jsou zadane parametrem s bity: XXAAABBB
// XX mod, ve kterem to pracuje
// AAA kod prvniho registru
// BBB kod druheho registru
// přesun ze segmentového registru od obecneho

int move8C(REG *regs, byte *memory)
{	
	byte RMcode;
	reg16 *reg1, *reg2;
	
	RMcode = memory[regs->ip+1];
	
	switch (getRMmode(RMcode))
	{
		case 3:		// mod 11, kde se pouzivaji pouze registry 
			reg2 = getRMsegment(2, RMcode, regs);
			reg1 = getRMregister(1, RMcode, regs);
			*reg1 = *reg2;
			
			if (DEBUG_MODE == 1)
				printf("Instrukce MOVE Segmetový REG do obecný REG \n");
		break;
		default:
			printf("nedefinovaný RM mod %d", getRMmode(RMcode));
			return(-1);
	}
	regs->ip+=2;
	return(0);
}

// Přesun v RM modu. Regostry jsou zadane parametrem s bity: XXAAABBB
// XX mod, ve kterem to pracuje
// AAA kod prvniho registru
// BBB kod druheho registru
// přesun z obecného  registru od segmentového

int move8E(REG *regs, byte *memory)
{	
	byte RMcode;
	reg16 *reg1, *reg2;
	
	RMcode = memory[regs->ip+1];
	
	switch (getRMmode(RMcode))
	{
		case 3:		// mod 11, kde se pouzivaji pouze registry
			reg2 = getRMregister(1, RMcode, regs);
			reg1 = getRMsegment(2, RMcode, regs);
			*reg1 = *reg2;
						
			if (DEBUG_MODE == 1)
				printf("Instrukce MOVE obecný REG do Segmetový REG \n");
			break;
		default:
			printf("nedefinovaný RM mod %d", getRMmode(RMcode));
			return(-1);
	}
	regs->ip+=2;
	return(0);
}


// xor operace Pracuje s obecnými regostry zadanými v R/M módu
 
int xor_instr(REG *regs, byte *memory)
{	
	byte param;
	reg16 *reg1, *reg2;
	if (regs->prefix == OPSIZE)
	{
		param = memory[regs->ip +1];
		regs->ip+=2;
		reg2 = getRMregister(1, param, regs);
		reg1 = getRMregister(2, param, regs);
		*reg1= *reg2 ^ *reg1;
	
		if (DEBUG_MODE == 1)
			printf("Instrukce XOR R/M mode \n");	
	}
	else
	{
		printf ("XOR bez prefixu nebyl implementován.\n");
		return(-1);
	}
	return(0);
}


// Přesouvá hodnotu do EBX
int moveEbx(REG *regs, byte *memory)
{	
	if (regs->prefix == 0)	
	{
		regs->bl = memory[regs->ip+1]; 					// nízký byte
		regs->bh =  memory[regs->ip+2] ; 				// vysoký byte
		regs->ip+=3;
		
		if (DEBUG_MODE == 1)
			printf("Instrukce MOVE do BX \n");		
	}
	else
	{
		printf ("MOVE BX s prefixem nebylo implementováno.\n");
		return(-1);
	}
	return(0);
}

// Přesouvá hodnotu do ESI
int moveEsi(REG *regs, byte *memory)
{	
	if (regs->prefix == 0)
	{
		regs->si = memory[regs->ip+1]; 					// nízký byte
		regs->si +=  memory[regs->ip+2] * 256; 	// vysoký byte
		regs->ip+=3;
		
		if (DEBUG_MODE == 1)
			printf("Instrukce MOVE do SI \n");		
	}
	else
	{
		printf ("MOVE SI s prefixem nebylo implementováno.\n");
		return(-1);
	}
	return(0);
}

// Přesouvá hodnotu do EDX
int moveEdx(REG *regs, byte *memory)
{	
	if (regs->prefix == 0)
	{
		regs->dl = memory[regs->ip+1]; 					// nízký byte
		regs->dh =  memory[regs->ip+2] ; 				// vysoký byte
		regs->ip+=3;
		
		if (DEBUG_MODE == 1)
			printf("Instrukce MOVE do DX \n");			
	}
	else
	{
		printf ("MOVEDX s prefixem nebylo implementováno.\n");
		return(-1);
	}
	return(0);
}


// Jednoduchý nepodmíněný skok
int jmp(REG *regs, byte *memory)
{	
	int jmp=0;
	jmp = memory[regs->ip+1];

	jmp = doplnek(jmp);	
	regs->ip += jmp;			// relativne skocim o minus jeden
	regs->ip += 2;
	
	if (DEBUG_MODE == 1)
		printf ("Instrukce JMP o %d\n", jmp);
		
	return(0);
}


// inkrement 
// je možné, že je ta instrukce FF obecnější a rozděluje se to módem
// ale já tady mám naštěstí jen tuto variantu
int inc(REG *regs, byte *memory)
{	
	byte RMcode=0;
	reg16 *reg;
	

	RMcode = memory[regs->ip+1];	
	
	reg = getRMregister(1, RMcode, regs);
	*reg = *reg+1;
	regs->ip+=2;
	
	if (DEBUG_MODE == 1)
		printf ("Instrukce INC RM mode\n");	
	return(0);
}


// součet
// opět rm mod pro obecne registry
int add(REG *regs, byte *memory)
{	
	byte RMcode=0;
	reg16 *reg1, *reg2;
	
	RMcode = memory[regs->ip+1];	
	
	reg1 = getRMregister(1, RMcode, regs);
	reg2 = getRMregister(2, RMcode, regs);
	*reg2 = *reg2 + *reg1;
	
	regs->ip+=2;
	if (DEBUG_MODE == 1)
		printf ("Instrukce ADD\n");
	return(0);
}



// Přesun v RM modu. Registry jsou zadane parametrem s bity: XXAAABBB
// XX mod, ve kterem to pracuje
// AAA kod prvniho registru
// BBB kod druheho registru
// přesun z obecného  registru od obecného

int move8A(REG *regs, byte *memory)
{	
	byte RMcode;
	reg16 *reg1, *reg2, addr;
	
	RMcode = memory[regs->ip+1];
	
	switch (getRMmode(RMcode))
	{
		case 0:		// mod 00, regiter + adresa
			reg1 = getRMregister(2,RMcode, regs);
			
			if (regs->prefix == 0)
			{
				addr =  memory[regs->ip+2]  + memory[regs->ip+3] * 256;
				*reg1 = memory[addr];
				if (DEBUG_MODE == 1)
					printf ("Instrukce MOVE z paměti %x do registru R/M \n", addr);
				regs->ip+=4;
			}
			if (regs->prefix == ADSIZE)
			{
				reg2 = getRMregister(1,RMcode, regs);
				//printf("reg2: %x sp: %x \n", reg2, &regs->sp);
				if (reg2 == &regs->sp)  //  jedna se o SIB mode (není to uplne ciste, mel bych napsat novou funkci pro RM8 namísto RM16
				{
					if (memory[regs->ip+2] == 6)		// ostatni rezimy neimplementovany
						addr = regs->ax + regs->si;
					regs->ip+=3;
					if (DEBUG_MODE == 1)
						printf ("Instrukce MOVE (SIB mode) z paměti %x, z adresy z registru do registru R/M \n", addr);
	
				}
				else
				{
					addr = *reg2;
					regs->ip+=2;
					if (DEBUG_MODE == 1)
						printf ("Instrukce MOVE z paměti %x, z adresy z registru do registru R/M \n", addr);
				}
				if (regs->espref == 0)			// osetreni prefixu ES
					addr += regs->ds;
				else
					addr += regs->es;
					
				*reg1 = memory[addr];
			}
				
			break;
		default:
			printf("nedefinovaný RM mod %d\n", getRMmode(RMcode));
			return(-1);
	}

	return(0);
}

// součet registru s hodnotou uloženou v paměti na zadané adrese

int addaddr(REG *regs, byte *memory)
{	
	byte RMcode=0;
	reg16 *reg1, *reg2, addr;
	
	RMcode = memory[regs->ip+1];	
	
	reg1 = getRMregister(2, RMcode, regs);
	reg2 = getRMregister(1, RMcode, regs);
	addr = *reg2;
	memory[addr] = memory[addr] + *reg1; 
	regs->ip+=2;
	
	if (DEBUG_MODE == 1)
		printf ("Instrukce ADD RM mode - K hodnotě na adrese %x přičítám hodnotu (%x) z registru \n", addr, *reg1);	
	return(0);
}

// inkrementace registru bx

int incebx(REG *regs, byte *memory)
{	
	regs->ip++;
	regs->bx = regs->bx + 1;
	
	if (DEBUG_MODE == 1)
		printf ("instrukce INC EBX\n");
	return(0);
}

// inkrementace regisytru dx

int incedx(REG *regs, byte *memory)
{	
	regs->ip++;
	regs->dx = regs->dx + 1;
	
	if (DEBUG_MODE == 1)
		printf ("instrukce INC EDX\n");
	return(0);
}

// dekremetace registru CX

int dececx(REG *regs, byte *memory)
{	
	regs->ip++;
	regs->cx = regs->cx - 1;
	
	if (DEBUG_MODE == 1)
		printf ("Instrukce DEC ECX\n");
	return(0);
}

// porovnání registru se zadanou hodnotou
// výsledek se uloží do stavové proměnné equal
// tímto výsledkem se pak řídí následující skok

int cmp(REG *regs, byte *memory)
{	
	byte RMcode=0;
	reg16 *reg1, *reg2, addr;
	
	RMcode = memory[regs->ip+1];	
	
	reg1 = getRMregister(1, RMcode, regs);
	if (*reg1 == memory[regs->ip+2])
		regs->equal = 1;
	else
		regs->equal = 0;
	
	if (DEBUG_MODE == 1)
		printf ("Instrukce CMP RM s hodnotou %x\n", memory[regs->ip+2]);
		
	regs->ip+=3;	
	return(0);
}

// skok na základě předchozího porovnání
// rozhoduje se na základě hodnoty v proměnné (preudoregistru) equals

int jne(REG *regs, byte *memory)
{	
	int jmp = 0;
	
	if (regs->equal == 1)
	{
		regs->ip+=2;
		if (DEBUG_MODE == 1)
			printf ("Instrukce JNE shoda, posun dal\n");
	}
	else
	{
		jmp = doplnek(memory[regs->ip+1]);
		regs->ip = regs->ip + jmp;
		regs->ip+=2;
		if (DEBUG_MODE == 1)
			printf ("Instrukce JNE skok o %d na %x\n", jmp, regs->ip);
	}
	return(0);
}

// zápis do registru AH

int moveah(REG *regs, byte *memory)
{	
	regs->ah = memory[regs->ip+1];	
	
	if (DEBUG_MODE == 1)
		printf ("MOVE do AH prictu %x\n", memory[regs->ip+1]);
	regs->ip+=2;	
	return(0);
}

// zápis do registru 

int movedi(REG *regs, byte *memory)
{	
		regs->di = memory[regs->ip+1]; 								// nízký byte
		regs->di +=  memory[regs->ip+2]  * 256; 				// vysoký byte
		regs->ip+=3;
		
	if (DEBUG_MODE == 1)
		printf ("MOVE do DI\n");
	return(0);
}

// Zápis do paměti, zdroj je zadaná hodnota, cíl paměťové místo dané registrem a zadanou adresou 

int movec7(REG *regs, byte *memory)
{	
	byte RMcode;
	reg16 *reg, addr, val;
	
	RMcode = memory[regs->ip+1];
	
	switch (getRMmode(RMcode))
	{
		case 2:		// mod 10, kde se pouzije adresa z registru + hodnota
			reg = getRMregister(1, RMcode, regs);
			addr =  regs->ds + *reg + memory[regs->ip+2] + memory[regs->ip+3] * 256;
			val = memory[regs->ip+4] + memory[regs->ip+5] * 256;
			memory[addr] = val;			
						
			if (DEBUG_MODE == 1)
				printf("Instrukce MOVE C7 na adresu DI+reg (%x) R/M hodnotu %x \n", addr, val);
			break;
		default:
			printf("nedefinovaný RM mod %d", getRMmode(RMcode));
			return(-1);
	}
	regs->ip+=6;
	return(0);
}
