/*
 *	Název:		fold2.cc
 * 	Řešení:		IJC-DU2, příklad 1b), 29.4.2014
 * 	Autor: 		Vojtech Mašek, FIT 1BIB xmasek15
 * 	Přeloženo: 	gcc-c++ 4.8.2
 * 
 * 	Poznakma: V zadani stoji " Poznámka: Pro zrychlení použijte 
 * 			std::ios::sync_with_stdio(false);", pri jeho pouziti sa ale 
 * 			stretavame s nevhodnym spravanim odhalenym valgrindom.
 * 			Je hlaseny error a namapovanu pamet.
 *			Fedora 19, valgrind 3.8.1
 * 			http://gcc.gnu.org/bugzilla/show_bug.cgi?id=27931
 * 			http://gcc.gnu.org/ml/libstdc++/2003-04/msg00427.html		
 */
 

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <getopt.h>

using namespace std;

void fold2(istream &stream, unsigned int N, string *line, bool crop_words)
{
	string word;
	bool written = false;
	bool LF=false;
	unsigned int chars = 0;
	
	while (getline(stream,*line))
	{
		if(!line->compare(""))
		{
			if(!LF)
				cout<<endl;
			cout<<endl;
			LF=true;
			written=false;
			chars=0;
		}
		else
		{
			LF=false;
			istringstream my_in(*line);
	
			while(my_in >> word)
			{
				if (chars+word.length() <= N)
				{
					if(written)
						cout << " " << word ;
					else
						cout <<word;
					written=true;	
					chars+=word.length()+1;
				}
				else
				{
					if(crop_words&&word.length()>N)
						word.erase(N);
					
					if(!chars)
						cout << word;
					else
						cout << endl << word;
					written=true;
					chars=word.length()+1;
				}
			}
		}
	}
	cout<<endl;
}

int main(int argc, char **argv)
{
	string line;
	
	unsigned int N=80;
	
// !!!! POZOR !!!!
ios::sync_with_stdio(false); ///ak je pouzite, valgrind hlasi error a namapovanu pamet

	bool crop_words = false;
	int optc;
	
	char *filename=nullptr;
	
	if(argc>1&&argv[1][0]!='-')
		filename=argv[1];

	while ((optc = getopt(argc, argv, ":w:c"))!=EOF)
	{
		switch (optc)
		{
			case 0:
				cerr << "NO ARGUMENTS" <<endl;
				return EXIT_FAILURE;
			case 'w':									/** Sirka riadkov */
				N=(unsigned int)atoi(optarg);
				if(N<1)
				{
					cerr << "WRONG WIDTH" <<endl;
					return EXIT_FAILURE;
				}
				break;
			case 'c':									/** Odrezavanie */
				crop_words = true;
				break;
			default:
				cerr << "WRONG ARGUMENTS" <<endl;
				return EXIT_FAILURE;
		}
    }
    
    if(filename)
	{
		ifstream file(filename);
		if(!file)
		{
			cerr << "FOPEN ERROR" << endl;
			return EXIT_FAILURE;
		}
		fold2(file,N,&line, crop_words);
		file.close();
	}
	else
		fold2(cin,N,&line, crop_words);
	
    return EXIT_SUCCESS;
}
