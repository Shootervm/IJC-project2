/*
 *	Název:		htab_lookup.c
 * 	Řešení:		IJC-DU2, příklad 2), 29.4.2014
 * 	Autor: 		Vojtech Mašek, FIT 1BIB xmasek15
 * 	Přeloženo: 	gcc 4.8.2
 */

#include "htable.h"

/**Doplni polozku do tabulky, ak tabulka uz polozku obsahuje zvysi
 * pocitadlo vyskytu polozky o jedna.
 * 
 * @param t - tabulka do ktorej bude polozka doplnena
 * @param key - pole znakov, polozka ktora bude doplnena
 * @return void
 */
 htab_items_t *htab_lookup(htab_t *t, const char *key)
{
	if(!t||!key)
	{
		fprintf(stderr, "[htab_lookup]\t-null pointer in args\n");
		return NULL;
	}
	
	unsigned int hash_index = hash_function(key, t->h_tab_size);	
	
	htab_items_t *item = t->h_tab_data[hash_index];

	while(item)
	{	
		if(!strcmp(key, item->key))	//ak sa kluc v polozke zhoduje s hladanym, vratime ukazatel na aktualnu polozku
		{
			item->data++;
			return item;
		}
		
		if (item->next)				//ak existuje dalsia polozka v liste prehlada sa jej kluc
			item = item->next;			//prepiseme ukazatel na aktuanu polozku ukazatelom na nasledujucu
		else 						//ak neexistuje cyklus ukoncime		
			break;
	}
	
	htab_items_t *old_item = item;
	
	item = calloc(sizeof(*item),1);
	if(!item)
		return NULL;
		
	item->key=calloc(strlen(key)+1,1); //alokacia pamete pre retazec + koncovu nulu
	if(!item->key)
	{
		free(item);		//uvolnenie pamete alokovanej pre item
		return NULL;
	}

	strcpy(item->key, key);	//nakopirovanie retazca
	item->data=1;			//retazec ma prave jeden vyskyt
	if(old_item)
		old_item->next=item;	//zaradenie na koniec zoznamu
	else
		t->h_tab_data[hash_index]=item;
		
	return item;
}
