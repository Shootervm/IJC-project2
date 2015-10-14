/*
 *	Název:		htab_statistics.c
 * 	Řešení:		IJC-DU2, příklad 2), 29.4.2014
 * 	Autor: 		Vojtech Mašek, FIT 1BIB xmasek15
 * 	Přeloženo: 	gcc 4.8.2
 */

#include "htable.h"

/**Vypise hodnoty vyskytu poloziek v tabulke.
 * 
 * 
 * @param t - tabulka ktore z poloziek bude vypis
 * @return void
 */
void htab_statistics(htab_t *t)
{
	if(!t)
	{
		fprintf(stderr, "[htab_statistics]\t-invalid table\n");
		return;
	}
	
	htab_items_t *item;
	
	unsigned int count=0, filled=0, n=0, min=(unsigned int)-1, max=0;
	
	for(unsigned int i=0; i<t->h_tab_size;i++)
	{
		if(t->h_tab_data[i])
		{
			filled++;
			item=t->h_tab_data[i];
			while(item)
			{
				n++;
				if(min>n)
					min=n;
				if(max<n)
					max=n;
				item=item->next;
			}
			//printf("LINE %u\tITEMS: %u\n",i,n); //moznost zapnut aj priebezne vypisovanie poloziek
			count+=n;
			n=0;
		}
	}
	printf("\tItems in lines:\nTOTAL:\t\t%u\nMIN:\t\t%u\nMAX:\t\t%u\nAVG:\t\t%.5f\nFILLED AVG\t%.5f\n",count,min,max, (float)count/t->h_tab_size, (float)count/filled);
	return;
}
