/*
 *	Název:		fold.c
 * 	Řešení:		IJC-DU2, příklad 1a), 29.4.2014
 * 	Autor: 		Vojtech Mašek, FIT 1BIB xmasek15
 * 	Přeloženo: 	gcc 4.8.2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#define LF 10
#define LIMIT 4096

void fold(FILE *stream, unsigned int N, int crop_words);
int FileOpen(const char *filename);

int main(int argc, char *argv[])
{
	int N = 80, crop_words = 0, optc;
	char *filename=NULL;
	
	if(argc>1&&argv[1][0]!='-')
		filename=argv[1];
	
	while ((optc = getopt(argc, argv, ":w:c"))!=EOF)
	{
		switch (optc)
		{
			case 0:
				fprintf(stderr,"NO ARGUMENTS\n");
				return EXIT_FAILURE;

			case 'w':									/** Sirka riadkov */
				N=atoi(optarg);
				if(N<1&&N>LIMIT)
				{
					fprintf(stderr,"WRONG WIDTH\n");
					return EXIT_FAILURE;
				}
				break;

			case 'c':									/** Odrezavanie */
				crop_words = 1;
				break;

			default:
				fprintf(stderr,"WRONG ARGUMENTS\n");
				return EXIT_FAILURE;
		}
    }

	if(filename)
	{
		FILE *file = fopen(filename, "rb");
		if (!file)
		{
			fprintf(stderr,"FOPEN ERROR\n");
			return EXIT_FAILURE;
		}
		fold(file, N, crop_words);
		fclose(file);
	}
	else
		fold(stdin, N, crop_words);


	return EXIT_SUCCESS;
}

void fold(FILE *stream, unsigned int N, int crop_words)
{
	char word[LIMIT+1]={0};
    unsigned int i=0, line=0;
    int ERR_LIMIT=0, c, prve=1, riadok=0, medzera=0;
    
    while(1)
    {
		c=fgetc(stream);
		while(c!=EOF)
		{
			if(i>=LIMIT)
			{
				if(!ERR_LIMIT)
				{
					fprintf(stderr, "LIMIT WORD CROP");
					ERR_LIMIT=1;
				}
				break;
			}	
			
			if(c==' '||c==LF)
			{
				if(c==LF)	riadok++;
				else 		medzera++;
				line+=(i+1);
				break;		
			}
			
			medzera=0; riadok=0;
			
			if(!crop_words||(crop_words&&i<N))
			{
				word[i]=(char)c;
				word[i+1]=0;
				i++;	
			}
			
			c=fgetc(stream);
		}
		
		if(i<=LIMIT)
		{
			if(riadok>1)
			{
				if(!prve)	printf("\n");
				printf("\n");
				line=0;
				prve=1;
			}
			else if(((line-1)<=N&&c!=EOF)||medzera>1)
			{
				if(prve||medzera>1)		printf("%s", word);
				else 					printf(" %s", word);
				word[0]=0;
				prve=0;
			}
			else
			{
				line=i+1;
				if(prve)				printf("%s", word);
				else 					printf("\n%s", word);
				word[0]=0;
				prve=0;
			}
		}
		
		if(c==EOF)
		{
			if(i>=LIMIT)				printf("\n");
			break;
		}
		
		if(i>=LIMIT)
			i++;
		else
			i=0;
	}
}
