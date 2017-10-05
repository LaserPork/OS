#include <stdio.h>
#include "dataTypes.h"
#include "instructions.h"
#include "tools.h"

int run(byte *memory)
{
	REG regs;																																	// sada registrů - jednoduše jako pole, pro indexy používám konstanty AX, BX atp.
	int (*interrupts[INTERRUPTS_COUNT]) (reg32 *registers, byte *memory);			// tabulka vektorů přerušení. Přišlo mi funny udělat to jako pole ukazatelů na funkce
	byte instr = 0;																															// aktuálně načtená instrukce
	int i, ret=0;
	
	// reset registrů 
	
	regs.ip = HEADER_SIZE;			// nastaveni instruction pointeru na konec hlavicky, tedy na první istrukci samotného kódu
	regs.cs = 0;
	regs.ds = 0;
	regs.es = 0;
	regs.ss = 0;
	regs.bp = HEADER_SIZE;
	regs.sp = SEGMENT_SIZE -2;	// size = 65536
	regs.prefix = 0;
	regs.espref = 0;
	regs.equal = 0;
	
	// nastaveni tabulky preruseni
	for (i=0; i<INTERRUPTS_COUNT; i++)
		interrupts[i] = NULL;
	interrupts[0x10] = int_10;
	interrupts[0x20] = int_20;
	interrupts[0x21] = int_21;
	
	while (1) 										// hlavní smyčka - bude to while(1), ale dokud nemám hotový INT21 je to for
	{
		instr = memory[regs.ip];		// nacteni instrukce z paměti 

		if (DEBUG_MODE == 1)
		{
			printf("INSTR: %x \n", instr);
		}

		// pokud je to jen prefix, tak jej uložím. Udělal jsem si pro jednoduchost prefixový register
		if (instr == OPSIZE || instr == ADSIZE || instr == ESPRF)
		{
			if (DEBUG_MODE == 1)
				printf ("Načítám prefix: %x (%d)\n", instr, instr);

			if (instr == ESPRF)
				regs.espref = 1;
			else	
				regs.prefix = instr;
			regs.ip++;
		}
		else	// když to není prefix je to instrukce
		{
			switch (instr)	// pro každou istrukci se volá extra funkce. Načtení parametrů a posun IP se dělá až v té funkci
			{
				case MOVEAX:	ret = moveEax(&regs, memory); break;
				case MOVEBX:	ret = moveEbx(&regs, memory); break;
				case MOVEDX:	ret = moveEdx(&regs, memory); break;
				case MOVESI:		ret = moveEsi(&regs, memory); break;
				case MOVE8C: 	ret = move8C(&regs, memory); break;
				case MOVE8E: 	ret = move8E(&regs, memory); break;
				case XOR:			ret = xor_instr(&regs, memory); break;
				case JMP:			ret = jmp(&regs, memory); break;
				case INC:				ret = inc(&regs, memory); break;
				case ADD:			ret = add(&regs, memory); break;
				case MOVE8A:	ret = move8A(&regs, memory); break;
				case INCEBX:		ret = incebx(&regs, memory); break;
				case INCEDX:		ret = incedx(&regs, memory); break;
				case DECECX:		ret = dececx(&regs, memory); break;
				case MOVEAH:	ret = moveah(&regs, memory); break;
				case ADDADDR:	ret = addaddr(&regs, memory); break;
				case CMP:			ret = cmp(&regs, memory); break;
				case JNE:				ret = jne(&regs, memory); break;
				case MOVEDI:		ret = movedi(&regs, memory); break;
				case MOVEC7:	ret = movec7(&regs, memory); break;
			
				case INT: 									// přerušení je trochu specifické, tak se řeší tady
					regs.ip++;
					instr = memory[regs.ip];	// cislo preruseni
					//printf("Definované přerušení %d (0x%x)\n", instr, instr);
						
					if (instr == END)
					{
						if (DEBUG_MODE == 1)
							printf("Konec programu. (INT 20h)\n");
						ret = (*interrupts[instr]) (&regs, memory);	
						return(0);
					}		
						
					if (*interrupts[instr] == NULL)
					{
						printf("Nedefinované přerušení %x (0x%x).\n", instr, instr);
						return(-1);
					}	
					
					ret = (*interrupts[instr]) (&regs, memory); //volani funkce, jejiz adresa je ulozena v tabulce preruseni
					break;
					
				default: regs.ip++;
			}
			regs.prefix = 0;	// pokud se provedla instrukce, resetuji se prefixy
			regs.espref = 0;
		}
		if (ret == -1)
		{
			printReg(&regs);
			printf("Při zpracování došlo k chybě.\n");
			return (-1);
		}
		
		if (DEBUG_MODE == 1)
			{
			printReg(&regs);
			getchar();
			}


	}	// for
	return 0;
}



int main(int argc, char **argv)
{
	
	byte *memory;										// segment - alokuji celý, 
	reg16 memPoi= HEADER_SIZE;			// ukazatel posledního zapsaného bytu v paměti - jen kvůli debug výpisu
	char *filename = "VB08.COM";			// datový soubor ve formátu .com
	int i, ret, c;
	FILE *fp;
	
	memory = malloc(SEGMENT_SIZE * sizeof(byte));
	if (memory == NULL) 
	{
		fprintf(stderr, "Chyba alokace paměti.\n");
		return(-1);
	}
	
	
	// vyčistění prostoru pro hlavičku 
	for (i=0; i<HEADER_SIZE; i++)		// nebudu jí řešit, vyplním nulama
		memory[i] = 0;	
	
	// načtení binárních dat ze souboru
	fp = fopen(filename,"rb");
	if (fp == NULL)
	{
		printf("Soubor se nepodařilo otevřít.\n");
		return -1;
	}
    while ((c = fgetc(fp)) != EOF)
    {
		memory[memPoi++] = (byte) c;
    }
	
	ret = run(memory);							// hlavní smyčka
		
	if (DEBUG_MODE == 1)
	{
		printf("Paměť: ");							// kontrolní výpis celého paměťového bloku
		for (i=0; i<memPoi; i++)
			printf("%x", memory[i]);
	}
	
	free(memory);
	return ret;
}
