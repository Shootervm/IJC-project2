/*
 *	Název:		htab_foreach.c
 * 	Řešení:		IJC-DU2, příklad 2), 29.4.2014
 * 	Autor: 		Vojtech Mašek, FIT 1BIB xmasek15
 * 	Přeloženo: 	gcc 4.8.2
 */

#include "htable.h"

/**Vykona nad kazdou polozkou v tabulke zadanu funkciu
 * 
 * @param t - tabulka nad ktorou budeme vykonavat operacie
 * @param function - funkcia, ktoru ideme vykonat nad polozkami
 * @return void
 */
 void htab_foreach(htab_t *t, Callback *function)
{
	if(!t||!function)
	{
		fprintf(stderr, "[htab_foreach]\t-null pointer in param.\n");
		return;
	}

	htab_items_t *item;
	
	for(unsigned int i=0; i < t->h_tab_size; i++) //postupne prejde vsetky riadky tabulky a vyvola funkciu nad kazdou polozkou
	{
		item=t->h_tab_data[i];
		while (item)
		{
			function(item->key, item->data);
			item=item->next;
		}
	}
	
	return;	
}
