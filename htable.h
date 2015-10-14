/*
 *	Název:		htable.h
 * 	Řešení:		IJC-DU2, příklad 2), 29.4.2014
 * 	Autor: 		Vojtech Mašek, FIT 1BIB xmasek15
 * 	Přeloženo: 	gcc 4.8.2
 */


#ifndef HTABLE_H
#define HTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//----------------------------------------------------------------------
/************************************************
 *	Datove struktury a definicie datovych typov	*
 ************************************************/
 
typedef struct htab_items htab_items_t;


struct htab_items
{
	char *key;						//ukazatel na dynamicky alokovany retazec
	unsigned int data;				//pocet vyskytov retazca
	htab_items_t *next;				//ukazatel na dalsi prvok
};


typedef struct htab
{
	unsigned int h_tab_size;		//velkost nasledujuceho pola ukazatelov
	htab_items_t *h_tab_data[];		//flexible pole ukazatelu na h
} htab_t;


typedef void (Callback)(const char*, unsigned int);

//----------------------------------------------------------------------
/************************************************
 *				Prototypy funkcii				*
 ************************************************/


/**Alkuje tabulku o velkosti size
 * 
 * @param size - velkost tabulky ktoru bude alokovat
 * @return htab_t* - ukazatel na alokovanu strukturu tabulky
 */
htab_t *htab_init(unsigned int size);


/**Doplni polozku do tabulky, ak tabulka uz polozku obsahuje zvysi
 * pocitadlo vyskytu polozky o jedna.
 * 
 * @param t - tabulka do ktorej bude polozka doplnena
 * @param key - pole znakov, polozka ktora bude doplnena
 * @return void
 */
htab_items_t *htab_lookup(htab_t *t, const char *key);


/**Vykona nad kazdou polozkou v tabulke zadanu funkciu
 * 
 * @param t - tabulka nad ktorou budeme vykonavat operacie
 * @param function - funkcia, ktoru ideme vykonat nad polozkami
 * @return void
 */
void htab_foreach(htab_t *t, Callback *function);


/**Vymaze polozky tabulky a uvolni pre ne alokovanu pamet.
 * 
 * @param t - tabulka ktorej polozky budu vymazane
 * @return void
 */
void htab_clear(htab_t *t);


/**Uvolni pamet alokovanu pre tabulku
 * 
 * @param t - tabulka ktorej alokovana pamet ma byt uvolnena
 * @return void
 */
void htab_free(htab_t *t);


/**Vyhlada polozku v htab_t a zmaze jej zaznam, v pripade ak ma polozka 
 * evidovanych viac vyskytov znizi pocitadlo o jedna.
 * 
 * @param t - tabulka z ktorej bude polozka vymazana
 * @param key - pole znakov, polozka ktora bude najdena a zmazana
 * @return void
 */
void htab_remove(htab_t *t, const char *key);


/**Vypise hodnoty vyskytu poloziek v tabulke
 * 
 * 
 * @param t - tabulka ktore z poloziek bude vypis
 * @return void
 */
void htab_statistics(htab_t *t);


/**Prevedie hash nad zadanym klucom podla velkosti zadanej zabulky
 * 
 * @param str			- pole znakov - kluc ktory hashujeme do tabulky
 * @param htab_size 	- velkost tabulky pre ktoru budeme hashovat
 * @return unsigned int - hash podla zadaneho kluca
 */
unsigned int hash_function(const char *str, unsigned htab_size);


//----------------------------------------------------------------------

#endif
