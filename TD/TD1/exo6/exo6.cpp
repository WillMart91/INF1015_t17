/*
Programme qui lit un dictionnaire, attribut un orthographe, une classe et une définition à un mot et retourne le mot le plus long
\fichier   exo6.cpp
\auteurs Sawka et Martin
\date   24 janvier 2022
Créé le 17 janvier 2022
*/

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
using namespace std;

const string FILE_NAME = "dictionnaire.txt";
const int NB_WORD = 4;

//structure d'un mot
//	spelling: le mot 
//	classGenre: la classe du mot et son genre
//	definition: la définition du mot
struct word
{
	string spelling;
	string classGenre;
	string definition;
}smallRobert[NB_WORD];

int main()
{
	ifstream file;
	file.open(FILE_NAME);
	string str;
	for (int i = 0; i < NB_WORD; i++)
	{
		getline(file, str);
		string valid[3];
		int cnt=0;
		for (int l = 0; l < str.size(); l++)
		{
			if (str[l] == '\t' || str[l]=='\n')
			{
				cnt++;
			}
			else
			{
				valid[cnt] += str[l];
			}
		}
		smallRobert[i].spelling = valid[0];
		smallRobert[i].classGenre = valid[1];
		smallRobert[i].definition = valid[2];
	}
	file.close();
	int iLong=0;
	for (int i = 1; i < NB_WORD; i++)
	{
		if (smallRobert[i].spelling.size()> smallRobert[iLong].spelling.size())
		{
			iLong = i;
		}
	}
	cout << smallRobert[iLong].spelling<<" (";
	cout << smallRobert[iLong].classGenre << ") : ";
	cout << smallRobert[iLong].definition;
}
