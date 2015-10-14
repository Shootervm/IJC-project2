/*
 *	Název:		io.c
 * 	Řešení:		IJC-DU2, příklad 2), 29.4.2014
 * 	Autor: 		Vojtech Mašek, FIT 1BIB xmasek15
 * 	Přeloženo: 	gcc 4.8.2
 */

#include "io.h"

int crop=0;

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
int fgetw(char *s, int max, FILE *f)
{
	if (!f||!s)
		return EOF;
		
	int i=0, c;

	if (max<1)
	{
		fprintf(stderr,"[fgetw]\t-invalid max limit\n");
		return EOF;
	}
	
	while(1)
	{
		if(i>=max)
		{
			if(!crop)
				fprintf(stderr,"[fgetw]\t-orezanie slov limit %d znakov\n", max);
			s[i]=0;
			c=fgetc(f);
			while(!isspace(c)&&c!=EOF)
			{
				c=fgetc(f);
				i++;
			}
			crop=1;
			return i;
		}	
		c=fgetc(f);
		
		if(c==EOF)
		{
			if(i)
				break;
			s[0]=0;
			return EOF;
		}
		else if(isspace(c))
		{
			if(i)
				break;
				
			continue;
		}
		s[i]=(char)c;
		i++;
	}
	s[i]=0;
	return i;
}
