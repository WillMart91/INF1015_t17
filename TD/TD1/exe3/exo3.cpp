/*
Ce programme a pour but de calculer la hauteur d'un objet après
un nombre x de rebonds selon plusieurs variables donné par l'utilisateur
\fichier   exo3.cpp
\auteurs  Sawka et Martin
\date   18 janvier 2022
Créé le 17 janvier 2022
*/

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;
const double gravity = 9.81;

/*
 Lit un nombre au clavier
  \param       message   le message demander a l'utilisateur
  \return  le  nombre
*/
double getNumber(string message)
{
    cout << message << " ";
    double number;
    string str;
    getline(cin, str);
    try {
        number = stof(str);
    }
    catch (exception)
    {
        cout << "ceci n'est pa un nombre flotant \n";
        number = getNumber(message);
    }
    return number;
}

/*
 valide si un nombre demander au clavier est entre 0 et la borne max
  \param       message   le message demander a l'utilisateur
  \param       max		 la valeur maxiamle du nombre
  \return  le  nombre
*/
double validateNumber(string message, double max = INFINITY)
{
    const double MIN = 0.0;
    double nb;
    do {
        nb = getNumber(message);
    } while ((nb < MIN) || (nb > max));
    return nb;
}


/*
 calcul la hauteur après un nombre de rebonds et affiche cette valeur
  \param       initialHeight   hauteur initiale
  \param       nbBounce        nombre de rebonds
  \param       coefficient     coeficient de rebonds
*/
void findHeight(double initialHeight, double nbBounce, double coefficient)
{
    double height = initialHeight;
    double speed = 0;

    for (int i = 0; i < nbBounce; i++)
    {
        speed = sqrt(2 * gravity * height);
        speed *= coefficient;
        height = pow(speed, 2) / (2 * gravity);
    }

    cout << "La hauteur apres " << nbBounce << " rebonds est de : " << height;

}

int main()
{
    double initialHeight = validateNumber("auteur initiale : ");
    int rebounds = validateNumber("Numéro du bond auquel on veut savoir la hauteur :");
    double coefficient = validateNumber("Coefficient de rebond (entre 0 et 1) : ", 1.0);

    findHeight(initialHeight, rebounds, coefficient);
}