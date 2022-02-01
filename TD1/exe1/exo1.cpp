
/*
Programme qui lit un nombre entier au clavier et determine s'il est premier
\fichier   exo1.cpp
\auteurs Sawka et Martin
\date   18 janvier 2022
Créé le 17 janvier 2022
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/*
 Lit un nombre au clavier
  \return  le  nombre
*/
int getNumber()
{
	string strMytestString = "please enter an integer ";
	cout << strMytestString;
	int nb;
	string str;
	getline(cin, str);
	try {
		nb = stoi(str);
	}
	catch (exception)
	{
		cout << "this is not an integer \n";
		nb = getNumber();
	}
	return nb;
}

/*
 affiche si un nombre demander est permier 
 et sinon affiche son plus petit diviseur
	\param    nb   le nombre a verifier
*/
void nombrePremier(int nb)
{
	if (nb % 2 != 0)
	{
		for (int i = 3; i <= sqrt(nb); i += 2)
		{
			if (nb % i == 0)
			{
				cout << "this is not a prime number " << i << "\n";
				break;
			}
		}
		cout << "this is a prime number \n";
	}
	else
	{
		cout << "this is not a prime number 2 \n";
	}
}



int main(int argc, char)
{
	int nb = getNumber();
	nombrePremier(nb);
	return 0;
}

