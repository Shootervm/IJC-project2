/*
 *	Název:		htab_clear.c
 * 	Řešení:		IJC-DU2, příklad 2), 29.4.2014
 * 	Autor: 		Vojtech Mašek, FIT 1BIB xmasek15
 * 	Přeloženo: 	gcc 4.8.2
 */

#include "htable.h"

/**Vymaze polozky tabulky a uvolni pre ne alokovanu pamet
 * 
 * @param t - tabulka ktorej polozky budu vymazane
 * @return void
 */
void htab_clear(htab_t *t)
{
	if(!t||!t->h_tab_data)
		return;
	
	htab_items_t *item=NULL;
	htab_items_t *next_item=NULL;
	
	for(unsigned int i=0; i<t->h_tab_size;i++)
	{
		if(t->h_tab_data[i])
		{
			item=t->h_tab_data[i];
			while(item)
			{
				if(item->key)
					free(item->key);
				
				next_item=item->next;
				free(item);
				item=next_item;
			}
			t->h_tab_data[i]=NULL;
		}
	}
	return;
}
