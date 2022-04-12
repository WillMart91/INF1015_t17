/*
Programme modifié du TP2, permettant ainsi l'ajout de classes génériques, de fonctions lamda,
								de pointeurs unique et partagés et de surcharges d'opérateurs
\fichier   structures.hpp
\auteurs Sawka et Martin
\date   6 mars 2022
Créé le 21 février 2022
*/

#pragma once
// Structures mémoires pour une collection de films.

#include <string>
#include <memory>
#pragma region "Includes"//{
#define _CRT_SECURE_NO_WARNINGS // On permet d'utiliser les fonctions de copies de chaînes qui sont considérées non sécuritaires.

#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>

#include "cppitertools/range.hpp"
#include "gsl/span"

#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp" // Nos fonctions pour le rapport de fuites de mémoire.
#include "debogage_memoire.hpp" 

using namespace std;

struct Film; struct Acteur; // Permet d'utiliser les types alors qu'ils seront défini après.


template <typename T>
class Liste {
private:
	int capacite_, nElements_;
	unique_ptr<shared_ptr<T>[]> elements_;
	// Pointeur vers un tableau de Acteur*, chaque Acteur* pointant vers un Acteur.
public:
	Liste();
	Liste(int cap,int nElem, const unique_ptr<shared_ptr<T>[]>& tab);
	Liste(const Liste& liste) {
		nElements_ = liste.nElements_;
		capacite_ = liste.capacite_;
		elements_ = make_unique<shared_ptr<T>[]>(capacite_);
		for (int i = 0; i < liste.nElements_; i++)
		{
			elements_[i] = liste.elements_[i];
		}
	}
	int getCapacite()const;
	shared_ptr<T>* getElements()const;
	int getNElements()const;
	void setElements(shared_ptr<T> newElem, int index);
	void setCapacite(int newCap);
	void setNElements(int newNElem);
	void afficher()const;
};
using ListeActeurs = Liste<Acteur>;

class ListeFilms {
public:
	//ListeFilms(); //code coverage
	ListeFilms(const string& nomFichier);
	int getNElements()const;
	Film** getElements()const;
	void ajouterFilm(Film* film);
	void retirerFilm(Film* film);
	Film* getElements(int index);
	void detruireListeFilms();
	void afficherListeFilms()const;
	Film*& operator[](int i);
	Film* trouverFilm(const function<bool(Film*&)>& critere);
private:
	int capacite_, nElements_;
	Film** elements_;
};

Film*& ListeFilms::operator[](int i)
{
	return elements_[i];
}

struct Film
{
	string titre = "None";
	string realisateur = "unknown"; // Titre et nom du réalisateur (on suppose qu'il n'y a qu'un réalisateur).
	int anneeSortie = 2022;
	int recette = 0; // Année de sortie et recette globale du film en millions de dollars
	ListeActeurs acteurs = ListeActeurs();
	friend ostream& operator<< (ostream& o, Film* film);
};

struct Acteur
{
	string nom ="unknown";
	int anneeNaissance=2022;
	char sexe='M';
};


