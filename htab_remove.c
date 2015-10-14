/*
 *	Název:		htab_remove.c
 * 	Řešení:		IJC-DU2, příklad 2), 29.4.2014
 * 	Autor: 		Vojtech Mašek, FIT 1BIB xmasek15
 * 	Přeloženo: 	gcc 4.8.2
 */

#include "htable.h"

/**Vyhlada polozku v htab_t a zmaze jej zaznam, v pripade ak ma polozka 
 * evidovanych viac vyskytov znizi pocitadlo o jedna.
 * 
 * @param t - tabulka z ktorej bude polozka vymazana
 * @param key - pole znakov, polozka ktora bude najdena a zmazana
 * @return void
 */
void htab_remove(htab_t *t, const char *key)
{
	if(!t||!key)
	{
		fprintf(stderr, "[htab_remove]\t-null pointer in param.\n");
		return;
	}
	
	unsigned int found=0, hash_index = hash_function(key, t->h_tab_size);
	
	htab_items_t *item = t->h_tab_data[hash_index];
	htab_items_t *old_item=NULL;
	
	while(item)
	{
		if(!strcmp(key, item->key))
		{
			found=1;
			break;
		}
		old_item=item;
		item = item->next;			
	}
	
	if(!found)
		return;
	
	if(old_item)
	{
		if(item->next)					//prvok ma na oboch stranach dalsie prvky //preskocenie vymazavaneho prvku
			old_item->next=item->next;
		else 							//vymazavany prvok bol posledny prvok v zozname
			old_item->next=NULL;
	}
	else 								//prvok je prvy v riadku
	{
		if(item->next)					//riadok obsahuje dalsie prvky
			t->h_tab_data[hash_index]=item->next;
		else 							//riadok je iba o jednej polozke
			t->h_tab_data[hash_index]=NULL;
	}
	
	free(item->key);
	item->next=NULL;
	free(item);	

	return;
}
