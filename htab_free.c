/*
 *	Název:		htab_free.c
 * 	Řešení:		IJC-DU2, příklad 2), 29.4.2014
 * 	Autor: 		Vojtech Mašek, FIT 1BIB xmasek15
 * 	Přeloženo: 	gcc 4.8.2
 */

#include "htable.h"

/**Uvolni pamet alokovanu pre tabulku
 * 
 * @param t - tabulka ktorej alokovana pamet ma byt uvolnena
 * @return void
 */
void htab_free(htab_t *t)
{
	if(!t)
		return;

	htab_clear(t);
	free(t);
	t=NULL;
}
