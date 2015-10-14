/*
 *	Název:		io.h
 * 	Řešení:		IJC-DU2, příklad 2), 29.4.2014
 * 	Autor: 		Vojtech Mašek, FIT 1BIB xmasek15
 * 	Přeloženo: 	gcc 4.8.2
 */


#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**Funkcia nacita jedno slovo zo suboru do zadaneho pola znakov a vracia
 * dlzku slova. Z dlhsich slov nacita prvych max-1 znakov, zvysok
 * preskoci. Vracia EOF ak je koniec suboru.
 * Poznámka: Slovo je souvislá posloupnost znaků oddělená isspace znaky.
 * 
 * @param s 	- pole znakov kam budeme ukladat nacitane znaky
 * @param max 	- implementacny limit na orezanie (127 znakov)
 * @param f		- ukazatel na otvoreny subor z ktoreho budeme citat
 * @return int	- pocet nacitanych znakov, ak koniec suboru -> EOF
 */
int fgetw(char *s, int max, FILE *f);

#endif
