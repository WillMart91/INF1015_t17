/*
Programme qui fait une approximation de pi en générant des points dans un cercle
\fichier   exo4.cpp
\auteurs Sawka et Martin
\date   24 janvier 2022
Créé le 17 janvier 2022
*/




#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;
const double PI = 3.141593;

/*
 génère un nombre (double) entre -1 et 1
  \return  le  nombre
*/
double generateAxisValue()
{
    double nb= (double) rand() / RAND_MAX;
	int sign = rand();
	return (nb * pow(-1,sign));
}

/*
 Lit un nombre au clavier
  \param       nbPts   le nombre de point à générer afin d'approximer pi
  \return  l'approximation de pi
*/
void piApproximation(int nbPts)
{
	int cptPtsInside = 0;
	for (int i = 0; i < nbPts; i++)
	{
		if (pow(generateAxisValue(), 2) + pow(generateAxisValue(), 2) < 1)
		{
			cptPtsInside++;
		}
	}
	double piApprox=cptPtsInside * 4.0 / nbPts;
	setfill(0);
	cout << " Pi approximate value is " << fixed << setprecision(7) <<piApprox ;
	cout << "\nThe relative gap is " << abs(piApprox - PI)/PI<<"\n";

}

/*
 Lit un nombre au clavier
  \return  le  nombre
*/
int getNumber()
{
	cout << "how many points do we generate ";
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
 valide si un nombre demander au clavier est entre 0 et la borne max
  \param       max		 la valeur maxiamle du nombre
  \return  le  nombre
*/
int validateNumber(double max = INFINITY)
{
	const double MIN = 0.0;
	int nb;
	do
	{
		nb = getNumber();
	} while ((nb < MIN) || (nb > max));
	return nb;
}

int main()
{
	srand(unsigned(time(nullptr)));
	int nbPts = validateNumber();
	piApproximation(nbPts);
}


