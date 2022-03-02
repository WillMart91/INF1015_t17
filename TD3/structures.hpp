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

//struct ListeFilms {
//	int capacite, nElements;
//	Film** elements; // Pointeur vers un tableau de Film*, chaque Film* pointant vers un Film.
//};

////////////class ListeActeurs {
////////////private:
////////////	int capacite_, nElements_;
////////////	unique_ptr<shared_ptr<Acteur> []> elements_;
////////////	// Pointeur vers un tableau de Acteur*, chaque Acteur* pointant vers un Acteur.
////////////public:
////////////	ListeActeurs();
////////////	ListeActeurs(const ListeActeurs& liste) {
////////////		nElements_ = liste.nElements_;
////////////		capacite_ = liste.capacite_;
////////////		elements_ = make_unique<shared_ptr<Acteur>[]>(capacite_);
////////////		for (int i = 0; i < liste.nElements_; i++)
////////////		{
////////////			elements_[i] = liste.elements_[i];
////////////		}
////////////	}
////////////	int getCapacite()const;
////////////	shared_ptr<Acteur>* getElements()const;
////////////	int getNElements()const;
////////////	void setElements(shared_ptr<Acteur> newElem, int index);
////////////	void setCapacite(int newCap);
////////////	void setNElements(int newNElem);
////////////};

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
	ListeFilms();
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
	//ListeFilms joueDans= ListeFilms();
	///////*Acteur(const Acteur& acteur) {
	//////	this->anneeNaissance = acteur.anneeNaissance;
	//////	this->nom = acteur.nom;
	//////	this->sexe = acteur.sexe;
	//////}*/
};
template <typename T>
Liste<T>::Liste()
{
	capacite_ = 1;
	nElements_ = 0;
	elements_ = make_unique<shared_ptr<T>[]>(capacite_);
}
template <typename T>
int Liste<T>::getCapacite() const
{
	return capacite_;
}
template <typename T>
shared_ptr<T>* Liste<T>::getElements() const
{
	return elements_.get();
}
template <typename T>
int Liste<T>::getNElements() const
{
	return nElements_;
}
template <typename T>
void Liste<T>::setElements(shared_ptr<T> newElem, int index)
{

	elements_[index] = newElem;

}
template <typename T>
void Liste<T>::setCapacite(int newCap)
{
	capacite_ = newCap;
	unique_ptr<shared_ptr<T> []> newElements = make_unique<shared_ptr<T> []>(capacite_);
	for(int i=0;i<nElements_;i++)
	{
		newElements[i]= elements_[i];
	}
	//elements_.get_deleter();
	elements_ = move(newElements);
}
template <typename T>
void Liste<T>::setNElements(int newNElem)
{
	nElements_ = newNElem;
}

template<typename T>
Liste<T>::Liste(int cap, int nElem, const unique_ptr<shared_ptr<T>[]>& tab)
{
	capacite_ = cap;
	nElements_ = nElem;
	elements_ = make_unique<shared_ptr<T>[]>(capacite_);
	for (int i = 0; i < nElements_; i++)
	{
		elements_[i] = tab[i];
	}
}

template<typename T>
void Liste<T>::afficher() const
{
	for (int i = 0; i < nElements_; i++)
	{
		cout << *elements_[i]<<endl;
	}
}
