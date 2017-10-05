#include <stdio.h>
#include "dataTypes.h"
#include "tools.h"

// řádkový výpis registrů pro kontrolu
void printReg(REG *regs)
{
	printf ("ax: %x ", regs->ax);
	printf ("bx: %x ", regs->bx);
	printf ("cx: %x ", regs->cx);
	printf ("dx: %x ", regs->dx);
	printf ("si: %x ", regs->si);
	printf ("di: %x ", regs->di);
	printf ("cs: %x ", regs->cs);
	printf ("ds: %x ", regs->ds);
	printf ("es: %x ", regs->es);
	printf ("ss: %x ", regs->ss);
	printf ("sp: %x ", regs->sp);
	printf ("bp: %x ", regs->bp);
	printf ("ip: %x ", regs->ip);
	printf ("fl: %x ", regs->flag);
	printf ("pref: %x ", regs->prefix);
	printf ("espr: %x ", regs->espref);
	printf("\n");	
}

// dekodování RM parametru
// vrací register (pro obecné registry) 
// position = 1|2  zda chceme znát první nebo druhý registr

reg16 *getRMregister(byte position, byte val, REG *regs)
{
	//if (DEBUG_MODE == 1)
		//printf ("getRMregister pozice: %d val před: 0x%x\n", position, val);
	if (position == 2)	// dekoduji druhy register
	{
		val <<= 2;			// smazani modu - prvni dva byty
		val >>= 5;			// osmazani nepotřebneho parametru
	}
	else
		val &= 7;			// nulovani prvnich 5 bitu tzn mod a druhy parametr
	
	//if (DEBUG_MODE == 1)
		//printf ("getRMregister val po: %d\n", val);
	switch (val)
		{
			case 0: return &regs->ax; break;
			case 1: return &regs->cx; break;
			case 2: return &regs->dx; break;
			case 3: return &regs->bx; break;
			case 4: return &regs->sp; break;
			case 5: return &regs->di; break;
			case 6: return &regs->si; break;
			case 7: return &regs->bx; break;
			       
			default:
				printf("neznámý registr.\n");
				return NULL;
				break;
		}
	}

// dekodování RM parametru
// vrací register (pro segmentové registry) 
// position = 1|2  zda chceme znát první nebo druhý registr

reg16 *getRMsegment(byte position, byte val, REG *regs)
{

	if (position == 2)	// dekoduji druhý register
	{
		val <<= 2;			// smazani modu - prvni dva byty
		val >>= 5;			// smazani nepotřebneho parametru
	}
	else
		val &= 7;			// nulovani prvnich 5 bitu tzn mod a druhy parametr	

	switch (val)
		{
			case 0: return &regs->es; break;
			case 1: return &regs->cs; break;
			case 3: return &regs->ds; break;
			default:
				printf("neznámý registr.\n");
				return NULL;
				break;
		}		
		
}

// dekodování RM parametru
// vrací mód reprezentovaný prvními dvěma byty
byte getRMmode(byte val)
{
	return val >> 6;
}

// obsluha přerušení

/*
Sets the video mode. This function will clear the screen unless bit 7 of the AL register is set.
 
Inputs :  AH = 00h   AL = Video Mode (add 128 to not clear the screen). 
Mode:
	03h: 80x25 Text, 16 colors, 8 pages
Outputs: (None)
 */
 
int int_10(REG *regs, byte *memory)
{
	int i;
	if (DEBUG_MODE == 1)
		printf("Spouštím INT 10h. Nastavuji mod obrazovky na 80x25 Text, 16 colors, 8 pages \n");
	
	// smazání displeje
	for (i=0; i< 80*25*2; i++)
		memory[DISPLAY_POINTER + i] = 0;
	
	regs->ip++;
	return(0);
}

int int_20(REG *regs, byte *memory)
{
	if (DEBUG_MODE == 1)
		printf("Spouštím INT 20h. \n");
		
	writeBuffer(memory);
}

/*
AH = 09h - WRITE STRING TO STANDARD OUTPUT

Entry: DS:DX -> '$'-terminated string
Return: AL = 24h

*/
 
 // zapisuje retezec do vystupniho obrazovkoveho bufferu
 
int int_21(REG *regs, byte *memory)
{
	int i, addr;
	byte c;
	
	if (DEBUG_MODE == 1)
		printf("Spouštím INT 21h. \n");
		
	for (i=0; i< 80*25*2; i++)	//nebudu riskovat zacyklení 
	{
		addr = regs->dx +i;	// ds ignoruji, je to tiny
		c =  memory[addr];
		if (c == STRING)
			break;
		//printf("%c (%x) ",c, c);
		memory[DISPLAY_POINTER + 2 * i] = c;	// zapisuji do bufferu na sudé pozice, liché jsou formátování
	}
		
	regs->ah = 1; // STRING;
	regs->ip++;
	return(0);
}

// zapisuje obrazovkovy buffer na obrazovku

void writeBuffer(byte *memory) 
{
	int i;
	byte c;
	
	//for (i=0; i< 80*25*2; i++)
	for (i=0; i< 300; i++)		// možná by stálo za to to vypisovat po řádcích OSX konzole na to trochu kašle
	{
		c = memory[DISPLAY_POINTER + 2 * i] ;	// nacitam znaky na sudych pozicich
		if (c > 0x20 && c < 0xff)
			printf("%c",c);
		else
			printf("%c", 0x20);
			
		c = memory[DISPLAY_POINTER + 2 * i +1];
		
		// je taky dost možný, že nejdříve musíš načíst atribit a pak znak jsem to moc nezkoumal
		// tady by se nejak vypsaly ty atributy jakoze treba takhle:
		/*
					#define KNRM  "\x1B[0m"
					#define KRED  "\x1B[31m"
					#define KGRN  "\x1B[32m"
					#define KYEL  "\x1B[33m"
					#define KBLU  "\x1B[34m"
					#define KMAG  "\x1B[35m"
					#define KCYN  "\x1B[36m"
					#define KWHT  "\x1B[37m"
					
					printf("%sred\n", KRED);
					printf("%sgreen\n", KGRN);
					printf("%syellow\n", KYEL);
					printf("%sblue\n", KBLU);
					printf("%smagenta\n", KMAG);
					printf("%scyan\n", KCYN);
					printf("%swhite\n", KWHT);
					printf("%snormal\n", KNRM);
			
		*/
	}	
	printf("\n");
	//printf("konecna adresa: %x \n", DISPLAY_POINTER + i);

}

// konverze bytu na doplněk
char doplnek(char value)
{
	value = ~value;
	value++;
	return 0 - value;
}
