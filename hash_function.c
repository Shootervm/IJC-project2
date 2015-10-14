/*
 *	Název:		hash_function.c
 * 	Řešení:		IJC-DU2, příklad 2), 29.4.2014
 * 	Autor: 		Vojtech Mašek, FIT 1BIB xmasek15
 * 	Přeloženo: 	gcc 4.8.2
 */

#include "htable.h"

/**Prevedie hash nad zadanym klucom podla velkosti zadanej zabulky
 * 
 * @param str			- pole znakov - kluc ktory hashujeme do tabulky
 * @param htab_size 	- velkost tabulky pre ktoru budeme hashovat
 * @return unsigned int - hash podla zadaneho kluca
 */
unsigned int hash_function(const char *str, unsigned htab_size) 
{
	unsigned int h=0;
	const unsigned char *p;
	for(p=(const unsigned char*)str; *p!='\0'; p++)
		h = 65599*h + *p;
	return h % htab_size;
}
