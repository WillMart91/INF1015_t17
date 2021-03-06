#pragma region "Includes"//{
#define _CRT_SECURE_NO_WARNINGS // On permet d'utiliser les fonctions de copies de chaînes qui sont considérées non sécuritaires.

#include "structures.hpp"      // Structures de données pour la collection de films en mémoire.

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>

#include "cppitertools/range.hpp"
#include "gsl/span"

#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp" // Nos fonctions pour le rapport de fuites de mémoire.
#include "debogage_memoire.hpp"        // Ajout des numéros de ligne des "new" dans le rapport de fuites.  Doit être après les include du système, qui peuvent utiliser des "placement new" (non supporté par notre ajout de numéros de lignes).

using namespace std;
using namespace iter;
using namespace gsl;

#pragma endregion//}

typedef uint8_t UInt8;
typedef uint16_t UInt16;

#pragma region "Fonctions de base pour lire le fichier binaire"//{

UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read((char*)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}

#pragma endregion//}

//TODO: Une fonction pour ajouter un Film à une ListeFilms,
//le film existant déjà; on veut uniquement ajouter le pointeur vers le film existant.
//Cette fonction doit doubler la taille du tableau alloué, avec au minimum un élément,
//dans le cas où la capacité est insuffisante pour ajouter l'élément.  
//Il faut alors allouer un nouveau tableau plus grand, 
//copier ce qu'il y avait dans l'ancien, et éliminer l'ancien trop petit.  
//Cette fonction ne doit copier aucun Film ni Acteur, elle doit copier uniquement des pointeurs.

void ajouterFilm(ListeFilms& liste, Film* film)
{
	Film** nouvelleListe;
	if (liste.capacite == 0)
	{
		liste.capacite = 1;
		nouvelleListe = new Film * [liste.capacite];
		delete[] liste.elements;
		liste.elements = nouvelleListe;
	}
	if (liste.capacite <= liste.nElements)
	{
		liste.capacite *= 2;
		nouvelleListe = new Film * [liste.capacite];
		for (int i : range(0, liste.nElements))
			nouvelleListe[i] = liste.elements[i];
		delete[] liste.elements;
		liste.elements = nouvelleListe;
	}
	liste.elements[liste.nElements++] = film;
}

//TODO: Une fonction pour enlever un Film d'une ListeFilms (enlever le pointeur) sans effacer le film;
//la fonction prenant en paramètre un pointeur vers le film à enlever.
//L'ordre des films dans la liste n'a pas à être conservé.
void retirerFilm(ListeFilms& liste, Film* film)
{
	for (int i : range(0, liste.nElements))
	{
		if (liste.elements[i] == film)
		{
			liste.elements[i] = liste.elements[--liste.nElements];
			liste.elements[liste.nElements] = nullptr;
			break;
		}
	} //non couverte en raison du break
}


//TODO: Une fonction pour trouver un Acteur par son nom dans une ListeFilms,
//qui retourne un pointeur vers l'acteur, ou nullptr si l'acteur n'est pas trouvé.  Devrait utiliser span.

Acteur* trouverActeur(const ListeFilms& liste, string nomActeur)
{
	//ListeActeurs listeActeur = {};//pas besoin
	//if (liste.elements == nullptr)
	//{
	//	return nullptr;
	//}
	for (Film*& film : span(liste.elements, liste.nElements))
	{
		//listeActeur = film->acteurs;
		for (Acteur*& acteur : span(film->acteurs.elements, film->acteurs.nElements))
		{
			if (acteur->nom == nomActeur)
				return acteur;
		}
	}
	return nullptr;
}

//TODO: Compléter les fonctions pour lire le fichier et créer/allouer une ListeFilms.
//La ListeFilms devra être passée entre les fonctions,
//pour vérifier l'existence d'un Acteur avant de l'allouer à nouveau (cherché par nom en utilisant la fonction ci-dessus).

Acteur* lireActeur(istream& fichier, ListeFilms& liste)
{
	Acteur acteur = {};
	acteur.nom = lireString(fichier);
	acteur.anneeNaissance = lireUint16(fichier);
	acteur.sexe = lireUint8(fichier);
	Acteur* ptrActeur = trouverActeur(liste, acteur.nom);

	if (ptrActeur == nullptr)
	{
		//cout << acteur.nom << "    ";
		acteur.joueDans.elements = new Film * [0];
		ptrActeur = new Acteur{};
		*ptrActeur = acteur;

	}
	return ptrActeur;
	//TODO: Retourner un pointeur soit vers un acteur existant ou un nouvel acteur ayant les bonnes informations,
	//selon si l'acteur existait déjà.  Pour fins de débogage, affichez les noms des acteurs crées;
	//vous ne devriez pas voir le même nom d'acteur affiché deux fois pour la création.
}

Film* lireFilm(istream& fichier, ListeFilms& liste)
{
	Film* film = new Film();
	film->titre = lireString(fichier);
	film->realisateur = lireString(fichier);
	film->anneeSortie = lireUint16(fichier);
	film->recette = lireUint16(fichier);
	film->acteurs.nElements = lireUint8(fichier);
	film->acteurs.capacite = film->acteurs.nElements;
	film->acteurs.elements = new Acteur * [film->acteurs.nElements];
	//NOTE: Vous avez le droit d'allouer d'un coup le tableau pour les acteurs, sans faire de réallocation comme pour ListeFilms.
	//Vous pouvez aussi copier-coller les fonctions d'allocation de ListeFilms ci-dessus dans des nouvelles fonctions et faire un remplacement de Film par Acteur, pour réutiliser cette réallocation.
	for (int i = 0; i < film->acteurs.nElements; i++)
	{

		Acteur* acteur = lireActeur(fichier, liste); //TODO: Placer l'acteur au bon endroit dans les acteurs du film.
		//TODO: Ajouter le film à la liste des films dans lesquels l'acteur joue.
		film->acteurs.elements[i] = acteur;
		ajouterFilm(acteur->joueDans, film);

	}
	//Film* ptrFilm = new Film{};
	//*ptrFilm = film;
	return film; //TODO: Retourner le pointeur vers le nouveau film.
}

ListeFilms creerListe(string nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	ListeFilms liste = { 0,0,new Film * [0] };
	int nElements = lireUint16(fichier);
	for (int i = 0; i < nElements; i++)
	{
		ajouterFilm(liste, lireFilm(fichier, liste)); //TODO: Ajouter le film à la liste.
	}

	return liste; //TODO: Retourner la liste de films.
}

//TODO: Une fonction pour détruire un film (relâcher toute la mémoire associée à ce film,
// et les acteurs qui ne jouent plus dans aucun films de la collection).
//Noter qu'il faut enleve le film détruit des films dans lesquels jouent les acteurs.
//Pour fins de débogage, affichez les noms des acteurs lors de leur destruction.
void detruireFilm(Film*& film)
{
	for (Acteur*& acteur : span(film->acteurs.elements, film->acteurs.nElements))
	{
		retirerFilm(acteur->joueDans, film);
		if (acteur->joueDans.nElements == 0)
		{
			//cout << acteur->nom<<endl;
			//delete& acteur->nom;
			//delete& acteur->anneeNaissance;
			//delete& acteur->sexe;
			delete[] & acteur->joueDans.elements[0]; 
			//delete[]& acteur->joueDans.elements;
			delete acteur;
		}
	}
	//cout << film->titre<<endl;
	delete[] film->acteurs.elements;
	delete film;
}
//TODO: Une fonction pour détruire une ListeFilms et tous les films qu'elle contient.
void detruireListeFilms(ListeFilms& liste)
{
	for (Film*& film : span(liste.elements, liste.nElements))
	{
		detruireFilm(film);
	}
	delete[] liste.elements;
	//delete& liste.nElements;
	//delete& liste.capacite;
	//delete[] &liste; //par sur si sa marche
}
void afficherActeur(const Acteur& acteur)
{
	cout << "  " << acteur.nom << ", " << acteur.anneeNaissance << " " << acteur.sexe << endl;
}

//TODO: Une fonction pour afficher un film avec tous ces acteurs (en utilisant la fonction afficherActeur ci-dessus).
void afficherFilm(const Film& film) //Film*& ou Film& ou Film*
{
	cout << "  " << film.titre << ", " << film.realisateur << ", " << film.anneeSortie << ", " << film.recette << endl;
	for (Acteur*& acteur : span(film.acteurs.elements, film.acteurs.nElements))
	{
		afficherActeur(*acteur);
	}
}

void afficherListeFilms(const ListeFilms& listeFilms)
{
	//TODO: Utiliser des caractères Unicode pour définir la ligne de séparation (différente des autres lignes de séparations dans ce progamme).
	static const string ligneDeSeparation = {};
	cout << ligneDeSeparation;
	//TODO: Changer le for pour utiliser un span.
	for (Film*& film : span(listeFilms.elements, listeFilms.nElements)) {
		afficherFilm(*film);
		cout << ligneDeSeparation;
	}
}

void afficherFilmographieActeur(const ListeFilms& listeFilms, const string& nomActeur)
{
	//TODO: Utiliser votre fonction pour trouver l'acteur (au lieu de le mettre à nullptr).
	const Acteur* acteur = trouverActeur(listeFilms, nomActeur);
	//if (acteur == nullptr)
	//	cout << "Aucun acteur de ce nom" << endl;
	//else
	afficherListeFilms(acteur->joueDans);
}

int main()
{
	bibliotheque_cours::activerCouleursAnsi();  // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par défaut.
	//int* fuite = new int; //TODO: Enlever cette ligne après avoir vérifié qu'il y a bien un "Fuite detectee" de "4 octets"
							//affiché à la fin de l'exécution, qui réfère à cette ligne du programme.
	static const string ligneDeSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";

	//TODO: Chaque TODO dans cette fonction devrait se faire en 1 ou 2 lignes, en appelant les fonctions écrites.
	//TODO: La ligne suivante devrait lire le fichier binaire en allouant la mémoire nécessaire.  Devrait afficher les noms de 20 acteurs sans doublons (par l'affichage pour fins de débogage dans votre fonction lireActeur).
	ListeFilms listeFilms = creerListe("films.bin");

	cout << ligneDeSeparation << "Le premier film de la liste est:" << endl;
	afficherFilm(*listeFilms.elements[0]); //TODO: Afficher le premier film de la liste.  Devrait être Alien.

	cout << ligneDeSeparation << "Les films sont:" << endl;
	afficherListeFilms(listeFilms);    //TODO: Afficher la liste des films.  Il devrait y en avoir 7.
	Film* f =listeFilms.elements[2];

	Acteur* acteur = trouverActeur(listeFilms, "Benedict Cumberbatch"); //TODO: Modifier l'année de naissance de Benedict Cumberbatch pour être 1976 (elle était 0 dans les données lues du fichier).
	acteur->anneeNaissance = 1976;                                        //Vous ne pouvez pas supposer l'ordre des films et des acteurs dans les listes, il faut y aller par son nom.
	cout << ligneDeSeparation << "Liste des films où Benedict Cumberbatch joue sont:" << endl;

	//TODO: Afficher la liste des films où Benedict Cumberbatch joue.  Il devrait y avoir Le Hobbit et Le jeu de l'imitation.
	afficherFilmographieActeur(listeFilms, acteur->nom); //un fuck? maybe

	//TODO: Détruire et enlever le premier film de la liste (Alien).  Ceci devrait "automatiquement" (par ce que font vos fonctions) détruire les acteurs Tom Skerritt et John Hurt, mais pas Sigourney Weaver puisqu'elle joue aussi dans Avatar.
	detruireFilm(listeFilms.elements[0]);
	retirerFilm(listeFilms, listeFilms.elements[0]);
	


	cout << ligneDeSeparation << "Les films sont maintenant:" << endl;
	afficherListeFilms(listeFilms); //TODO: Afficher la liste des films.

	//TODO: Faire les appels qui manquent pour avoir 0% de lignes non exécutées dans le programme (aucune ligne rouge dans la couverture de code; 
			//c'est normal que les lignes de "new" et "delete" soient jaunes).  Vous avez aussi le droit d'effacer les lignes 
			//du programmes qui ne sont pas exécutée, si finalement vous pensez qu'elle ne sont pas utiles.



	//TODO: Détruire tout avant de terminer le programme.  La bibliothèque de verification_allocation devrait afficher "Aucune fuite detectee." 
			//a la sortie du programme; il affichera "Fuite detectee:" avec la liste des blocs, s'il manque des delete.
	detruireListeFilms(listeFilms);
	return 0;
}