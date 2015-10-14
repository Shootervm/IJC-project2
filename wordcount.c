/*
 *	Název:		wordcount.h
 * 	Řešení:		IJC-DU2, příklad b), 29.4.2014
 * 	Autor: 		Vojtech Mašek, FIT 1BIB xmasek15
 * 	Přeloženo: 	gcc 4.8.2
 */

#include "htable.h"
#include "io.h"


/**Velkost hash tabulky.
 * Bola zvolena najvhodnejsia hodnota, prvocislo, tak aby sme dosahovali
 * co najnizsiu chybovost. Z tabulky uverejnenej na odkaze nizsie mi ako
 * nalepsie riesenie v pomere rozsahu tabulky a chyb prvocislo 12289.
 * http://planetmath.org/GoodHashTablePrimes
 */
#define HTAB_SIZE 12289U

/**
 * Implementacny limit pre orezavanie slov.
 */
#define WORD_LIMIT 127

/**
 * Funkcia ktora bude spustana nad jednotlivimi polozkami tabulky.
 */
void print_items(const char *key, unsigned int data)
{
	printf("%s\t%d\n", key, data);
}

/**
 * Prepis programu wordcount z C++ do C zo zadania.
 */
int main(void)
{

	htab_t *t=htab_init(HTAB_SIZE);
	if(!t)
	{
		fprintf(stderr, "[wordcount]\t-htable was not allocated\n");
		return EXIT_FAILURE;
	}
	
	char word[WORD_LIMIT+1]={0};

	
	while(fgetw(word, WORD_LIMIT, stdin)!=EOF)
	{
		if(!htab_lookup(t, word))
		{
			fprintf(stderr, "[wordcount]\t-[htab_lookup] allocation fail\n");
			htab_free(t);
			return EXIT_FAILURE;
		}
	}


	htab_foreach(t, &print_items);
	
	//htab_statistics(t); /// vypis statistiky udajov tabulky
	
	htab_free(t);
	return EXIT_SUCCESS;
}
