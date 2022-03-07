#pragma once
// Structures mémoires pour une collection de films.

#include <string>

using namespace std;

struct Film; struct Acteur; // Permet d'utiliser les types alors qu'ils seront défini après.

//struct ListeFilms {
//	int capacite, nElements;
//	Film** elements; // Pointeur vers un tableau de Film*, chaque Film* pointant vers un Film.
//};

struct ListeActeurs {
	int capacite, nElements;
	Acteur** elements; // Pointeur vers un tableau de Acteur*, chaque Acteur* pointant vers un Acteur.
};
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
private:
	int capacite_, nElements_;
	Film** elements_;
};

struct Film
{
	string titre, realisateur; // Titre et nom du réalisateur (on suppose qu'il n'y a qu'un réalisateur).
	int anneeSortie, recette; // Année de sortie et recette globale du film en millions de dollars
	ListeActeurs acteurs;
};

struct Acteur
{
	string nom; int anneeNaissance; char sexe;
	ListeFilms joueDans;
};
