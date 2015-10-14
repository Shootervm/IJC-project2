/*
 *	Název:		htab_init.c
 * 	Řešení:		IJC-DU2, příklad 2), 29.4.2014
 * 	Autor: 		Vojtech Mašek, FIT 1BIB xmasek15
 * 	Přeloženo: 	gcc 4.8.2
 */

#include "htable.h"

/**Alkuje tabulku o velkosti size
 * 
 * @param size - velkost tabulky ktoru bude alokovat
 * @return htab_t* - ukazatel na alokovanu strukturu tabulky
 */
htab_t *htab_init(unsigned int size)
{
	//alokacia dat pre tabulku s dynamicky velkym polom ukazatelov ktore su vdaka calloc naplnene "0" a budu tak brane ako NULL
	htab_t *t=calloc(sizeof(*t) + size * sizeof(htab_items_t*),1);
	if (!t)
		return NULL;
		
	//zapis alokacnej velkosti do tabulky
	t->h_tab_size = size;
	
	return t;
}

