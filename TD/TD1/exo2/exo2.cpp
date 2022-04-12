/*
Programme qui détermine la duree d'un remboursement d'un pret
 \ficher   exo2.cpp
 \auteurs Sawka et Martin
 \date   18 janvier 2022
 Créé le 17 janvier 2022
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;
const double MONTH_PER_YEAR = 12.0;
const double MAX_PERCENTAGE = 100.0;
/*
 Lit un nombre au clavier
  \param       message   le message demander a l'utilisateur
  \return  le  nombre
*/
double getNumber(string message)
{
	cout << message << " ";
	double nb;
	string str;
	getline(cin, str);
	try {
		nb = stof(str);
	}
	catch (exception)
	{
		cout << "is not a doubleing number \n";
		nb = getNumber(message);
	}
	return nb;
}


/*
 valide si un nombre demander au clavier est entre 0 et la borne max
  \param       message   le message demander a l'utilisateur
  \param	   max		 la valeur maxiamle du nombre
  \return  le  nombre
*/
double validateNumber(string message, double max = INFINITY)
{
	const double MIN = 0.0;
	double nb;
	do
	{
		nb = getNumber(message);
	}while ((nb < MIN) || (nb > max));
	return nb;
}

/*
 calcule la duree d'un paiement avec les valeurs demander
  \return  la duree du paiement en mois
*/
int dureePayment()
{
	int nbMonth=0;
	double loan = validateNumber("loan ammount");
	double payment = validateNumber("monthly payment",loan);
	double annualRate = validateNumber("annual interest rate in %", 100.0);
	double monthlyRate = annualRate / MONTH_PER_YEAR;
	do 
	{
		loan *= 1.0 + monthlyRate / MAX_PERCENTAGE;
		loan -= payment; 
		nbMonth++;
	} while (loan > 0.0);
	return nbMonth;
}

int main()
{
	cout << dureePayment();
}