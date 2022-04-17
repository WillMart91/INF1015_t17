/*
Programme modifié du TP2, permettant ainsi l'ajout de classes génériques, de fonctions lamda,
								de pointeurs unique et partagés et de surcharges d'opérateurs
\fichier   td2.cpp
\auteurs Sawka et Martin
\date   6 mars 2022
Créé le 21 février 2022
*/




#include "structures.hpp"      // Structures de données pour la collection de films en mémoire.

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

void ListeFilms::ajouterFilm(Film* film)
{
	Film** nouvelleListe;
	if (capacite_ <= nElements_)
	{
		capacite_ *= 2;
		nouvelleListe = new Film * [capacite_];
		for (int i : range(nElements_))
			nouvelleListe[i] = elements_[i];
		delete[] elements_;
		elements_ = nouvelleListe;
	}
	elements_[nElements_++] = film;
}

//TODO: Une fonction pour enlever un Film d'une ListeFilms (enlever le pointeur) sans effacer le film;
//la fonction prenant en paramètre un pointeur vers le film à enlever.
//L'ordre des films dans la liste n'a pas à être conservé.
void ListeFilms::retirerFilm(Film* film)
{
	for (int i : range(nElements_))
	{
		if (elements_[i] == film)
		{
			elements_[i] = elements_[--nElements_];
			elements_[nElements_] = nullptr;
		}
	} 
}


//TODO: Une fonction pour trouver un Acteur par son nom dans une ListeFilms,
//qui retourne un pointeur vers l'acteur, ou nullptr si l'acteur n'est pas trouvé.  Devrait utiliser span.

shared_ptr<Acteur> trouverActeur(const ListeFilms& liste, string nomActeur)
{
	for (Film*& film : span(liste.getElements(), liste.getNElements()))
	{
		//listeActeur = film->acteurs;
		for (shared_ptr<Acteur>& acteur : span(film->acteurs.getElements(), film->acteurs.getNElements()))
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

shared_ptr<Acteur> lireActeur(istream& fichier, ListeFilms& liste)
{
	Acteur acteur = {};
	acteur.nom = lireString(fichier);
	acteur.anneeNaissance = lireUint16(fichier);
	acteur.sexe = lireUint8(fichier);

	shared_ptr<Acteur> ptrActeur = trouverActeur(liste, acteur.nom);

	if (ptrActeur == nullptr) {
		return make_shared<Acteur>(acteur);
	}

	return ptrActeur;
}

Film* lireFilm(istream& fichier, ListeFilms& liste)
{
	Film* film = new Film();
	film->titre = lireString(fichier);
	film->realisateur = lireString(fichier);
	film->anneeSortie = lireUint16(fichier);
	film->recette = lireUint16(fichier);
	film->acteurs.setCapacite(lireUint8(fichier));

	for (int i :range(film->acteurs.getCapacite()))
	{

		shared_ptr<Acteur> acteur = lireActeur(fichier, liste); //TODO: Placer l'acteur au bon endroit dans les acteurs du film.
		//TODO: Ajouter le film à la liste des films dans lesquels l'acteur joue.
		film->acteurs.setElements(acteur,i);
		film->acteurs.setNElements((film->acteurs.getNElements())+1);
	}
	return film; //TODO: Retourner le pointeur vers le nouveau film.
}


//TODO: Une fonction pour détruire un film (relâcher toute la mémoire associée à ce film,
// et les acteurs qui ne jouent plus dans aucun films de la collection).
//Noter qu'il faut enleve le film détruit des films dans lesquels jouent les acteurs.
//Pour fins de débogage, affichez les noms des acteurs lors de leur destruction.
void detruireFilm(Film*& film) {
	delete film;
}
//TODO: Une fonction pour détruire une ListeFilms et tous les films qu'elle contient.
void ListeFilms::detruireListeFilms()
{
	for (Film*& film : span(elements_, nElements_))
	{
		detruireFilm(film);
	}
	delete[] elements_;
}

void afficherFilm(Film* film) {
	cout << (film);
}

void ListeFilms::afficherListeFilms()const
{
	//TODO: Utiliser des caractères Unicode pour définir la ligne de séparation (différente des autres lignes de séparations dans ce progamme).
	static const char16_t ligneCar = '\u005F';
	cout << string(50,ligneCar)<<endl;
	//TODO: Changer le for pour utiliser un span.
	for (Film*& film : span(elements_, nElements_)) {
		afficherFilm(film);
		cout << string(50, ligneCar)<<endl;
	}
}

int main()
{
	bibliotheque_cours::activerCouleursAnsi();  // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par défaut.
	//int* fuite = new int; //TODO: Enlever cette ligne après avoir vérifié qu'il y a bien un "Fuite detectee" de "4 octets"
							//affiché à la fin de l'exécution, qui réfère à cette ligne du programme.
	static const string ligneDeSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";

	//TODO: Chaque TODO dans cette fonction devrait se faire en 1 ou 2 lignes, en appelant les fonctions écrites.
	//TODO: La ligne suivante devrait lire le fichier binaire en allouant la mémoire nécessaire.  Devrait afficher les noms de 20 acteurs sans doublons (par l'affichage pour fins de débogage dans votre fonction lireActeur).
	ListeFilms listeFilms = ListeFilms("films.bin");

	cout << ligneDeSeparation << "Le premier film de la liste est:" << endl;
	afficherFilm(listeFilms.getElements(0)); //TODO: Afficher le premier film de la liste.  Devrait être Alien.

	cout << ligneDeSeparation << "Les films sont:" << endl;
	listeFilms.afficherListeFilms();    //TODO: Afficher la liste des films.  Il devrait y en avoir 7.

	shared_ptr<Acteur> acteur = trouverActeur(listeFilms, "Benedict Cumberbatch"); //TODO: Modifier l'année de naissance de Benedict Cumberbatch pour être 1976 (elle était 0 dans les données lues du fichier).
	acteur->anneeNaissance = 1976;                                        //Vous ne pouvez pas supposer l'ordre des films et des acteurs dans les listes, il faut y aller par son nom.
	cout << ligneDeSeparation << "Liste des films où Benedict Cumberbatch joue sont:" << endl;

	//TODO: Afficher la liste des films où Benedict Cumberbatch joue.  Il devrait y avoir Le Hobbit et Le jeu de l'imitation.
	//////////afficherFilmographieActeur(listeFilms, acteur->nom); //un fuck? maybe

	Film skylien = *listeFilms[0];
	skylien.titre = "Skylien";
	skylien.acteurs.setElements(listeFilms[1]->acteurs.getElements()[0], 0);
	skylien.acteurs.getElements()[0].get()->nom = "Daniel Wroughton Craig";
	afficherFilm(&skylien);
	afficherFilm(listeFilms.getElements(0));
	afficherFilm(listeFilms.getElements(1));
	

	Film* filmTrouver = listeFilms.trouverFilm([](Film*& f) mutable {return f->recette == 955;  });
	afficherFilm(filmTrouver);


	//TODO: Détruire et enlever le premier film de la liste (Alien).  Ceci devrait "automatiquement" (par ce que font vos fonctions) détruire les acteurs Tom Skerritt et John Hurt, mais pas Sigourney Weaver puisqu'elle joue aussi dans Avatar.
	detruireFilm(listeFilms.getElements()[0]);
	listeFilms.retirerFilm(listeFilms.getElements(0));

	

	cout << ligneDeSeparation << "Les films sont maintenant:" << endl;
	listeFilms.afficherListeFilms(); //TODO: Afficher la liste des films.

	//TODO: Faire les appels qui manquent pour avoir 0% de lignes non exécutées dans le programme (aucune ligne rouge dans la couverture de code; 
			//c'est normal que les lignes de "new" et "delete" soient jaunes).  Vous avez aussi le droit d'effacer les lignes 
			//du programmes qui ne sont pas exécutée, si finalement vous pensez qu'elle ne sont pas utiles.
	shared_ptr<string> ps1(new string("hello"));
	shared_ptr<string> ps2(new string("world"));
	unique_ptr<shared_ptr<string>[]> stringTab = make_unique<shared_ptr<string>[]>(2);
	stringTab[0] = ps1;
	stringTab[1] = ps2;
	Liste<string> listeTextes = Liste(2, 2, stringTab);
	Liste<string> listeTextes2 = listeTextes;
	shared_ptr<string> ps3(new string("hello world"));
	listeTextes.setElements(ps3, 0);
	*listeTextes.getElements()[1]="bye";

	listeTextes.afficher();
	listeTextes2.afficher();


	//TODO: Détruire tout avant de terminer le programme.  La bibliothèque de verification_allocation devrait afficher "Aucune fuite detectee." 
			//a la sortie du programme; il affichera "Fuite detectee:" avec la liste des blocs, s'il manque des delete.
	listeFilms.detruireListeFilms();
	return 0;
}
int ListeFilms::getNElements() const {
	return nElements_;
}
Film** ListeFilms::getElements()const {
	return elements_;
}
Film* ListeFilms::getElements(int index) {
	return elements_[index];
}

ListeFilms::ListeFilms(const string& nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	int nElements = lireUint16(fichier);
	capacite_ = 1;
	nElements_ = 0;
	elements_ = new Film * [capacite_];

	for (int i : range(nElements)) 
	{
		i;
		(*this).ajouterFilm(lireFilm(fichier, *this)); //TODO: Ajouter le film à la liste.
	}
}
ostream& operator<<(ostream& o, Film* film)
{
	o << "  " << film->titre << ", " << film->realisateur << ", " << film->anneeSortie << ", " << film->recette << endl;
	for (shared_ptr<Acteur>& acteur : span(film->acteurs.getElements(), film->acteurs.getNElements())) {
		o << "  " << acteur.get()->nom << ", " << acteur.get()->anneeNaissance << " " << acteur.get()->sexe << endl;
	}
	return o;
}

Film* ListeFilms::trouverFilm(const function<bool(Film*&)>& critere)
{
	for (Film*& f: span(elements_,nElements_) )
	{
		if (critere(f))
			return f;
	}
	//return nullptr; //cela n'arrive jamais --> couverture de code
}

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
	unique_ptr<shared_ptr<T>[]> newElements = make_unique<shared_ptr<T>[]>(capacite_);
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
	for (int i : range(nElements_))
	{
		elements_[i] = tab[i];
	}
}

template<typename T>
void Liste<T>::afficher() const
{
	for (int i : range(nElements_))  
	{
		cout << *elements_[i] << endl;
	}
}