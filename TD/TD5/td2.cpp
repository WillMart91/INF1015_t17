// Solutionnaire du TD4 INF1015 hiver 2022
// Par Francois-R.Boyer@PolyMtl.ca

#pragma region "Includes"//{
#define _CRT_SECURE_NO_WARNINGS // On permet d'utiliser les fonctions de copies de chaînes qui sont considérées non sécuritaires.

#include "structures.hpp"      // Structures de données pour la collection de films en mémoire.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>
#include <sstream>
#include "cppitertools/range.hpp"
#include "cppitertools/enumerate.hpp"
#include "gsl/span"
#include <forward_list>
#include <typeinfo>
#include<numeric>

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif

#if __has_include("bibliotheque_cours.hpp")
#include "bibliotheque_cours.hpp"
#define BIBLIOTHEQUE_COURS_INCLUS
using bibliotheque_cours::cdbg;
#else
auto& cdbg = clog;
#endif

#if __has_include("verification_allocation.hpp")
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette entête si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.
#endif

void initialiserBibliothequeCours([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	#ifdef BIBLIOTHEQUE_COURS_INCLUS
	bibliotheque_cours::activerCouleursAnsi();  // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par défaut.

	// cdbg.setTee(&clog);  // Décommenter cette ligne pour que cdbg affiche sur la console en plus de la "Sortie" du débogueur.
	
	bibliotheque_cours::executerGoogleTest(argc, argv); // Attention de ne rien afficher avant cette ligne, sinon l'Explorateur de tests va tenter de lire votre affichage comme un résultat de test.
	#endif
}

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

// Fonctions pour ajouter un Film à une ListeFilms.
//[
void ListeFilms::changeDimension(int nouvelleCapacite)
{
	Film** nouvelleListe = new Film*[nouvelleCapacite];
	
	if (elements != nullptr) {  // Noter que ce test n'est pas nécessaire puique nElements sera zéro si elements est nul, donc la boucle ne tentera pas de faire de copie, et on a le droit de faire delete sur un pointeur nul (ça ne fait rien).
		nElements = min(nouvelleCapacite, nElements);
		for (int i : range(nElements))
			nouvelleListe[i] = elements[i];
		delete[] elements;
	}
	
	elements = nouvelleListe;
	capacite = nouvelleCapacite;
}

void ListeFilms::ajouterFilm(Film* film)
{
	if (nElements == capacite)
		changeDimension(max(1, capacite * 2));
	elements[nElements++] = film;
}
//]

// Fonction pour enlever un Film d'une ListeFilms (enlever le pointeur) sans effacer le film; la fonction prenant en paramètre un pointeur vers le film à enlever.  L'ordre des films dans la liste n'a pas à être conservé.
//[
// On a juste fait une version const qui retourne un span non const.  C'est valide puisque c'est la struct qui est const et non ce qu'elle pointe.  Ça ne va peut-être pas bien dans l'idée qu'on ne devrait pas pouvoir modifier une liste const, mais il y aurais alors plusieurs fonctions à écrire en version const et non-const pour que ça fonctionne bien, et ce n'est pas le but du TD (il n'a pas encore vraiment de manière propre en C++ de définir les deux d'un coup).
span<Film*> ListeFilms::enSpan() const { return span(elements, nElements); }

//void ListeFilms::enleverFilm(const Film* film)  // Pas utile dans ce TD
//{
//	for (Film*& element : enSpan()) {  // Doit être une référence au pointeur pour pouvoir le modifier.
//		if (element == film) {
//			if (nElements > 1)
//				element = elements[nElements - 1];
//			nElements--;
//			return;
//		}
//	}
//}
//]

// Fonction pour trouver un Acteur par son nom dans une ListeFilms, qui retourne un pointeur vers l'acteur, ou nullptr si l'acteur n'est pas trouvé.  Devrait utiliser span.
//[

//NOTE: Doit retourner un Acteur modifiable, sinon on ne peut pas l'utiliser pour modifier l'acteur tel que demandé dans le main, et on ne veut pas faire écrire deux versions.
shared_ptr<Acteur> ListeFilms::trouverActeur(const string& nomActeur) const
{
	for (const Film* film : enSpan()) {
		for (const shared_ptr<Acteur>& acteur : film->acteurs.enSpan()) {
			if (acteur->nom == nomActeur)
				return acteur;
		}
	}
	return nullptr;
}
//]

// Les fonctions pour lire le fichier et créer/allouer une ListeFilms.

shared_ptr<Acteur> lireActeur(istream& fichier, const ListeFilms& listeFilms)
{
	Acteur acteur = {};
	acteur.nom            = lireString(fichier);
	acteur.anneeNaissance = lireUint16 (fichier);
	acteur.sexe           = lireUint8  (fichier);

	shared_ptr<Acteur> acteurExistant = listeFilms.trouverActeur(acteur.nom);
	if (acteurExistant != nullptr)
		return acteurExistant;
	else {
		cout << "Création Acteur " << acteur.nom << endl;
		return make_shared<Acteur>(move(acteur));  // Le move n'est pas nécessaire mais permet de transférer le texte du nom sans le copier.
	}
}

Film* lireFilm(istream& fichier, ListeFilms& listeFilms)
{
	Film* film = new Film;
	film->titre       = lireString(fichier);
	film->realisateur = lireString(fichier);
	film->anneeSortie = lireUint16 (fichier);
	film->recette     = lireUint16 (fichier);
	auto nActeurs = lireUint8 (fichier);
	film->acteurs = ListeActeurs(nActeurs);  // On n'a pas fait de méthode pour changer la taille d'allocation, seulement un constructeur qui prend la capacité.  Pour que cette affectation fonctionne, il faut s'assurer qu'on a un operator= de move pour ListeActeurs.
	cout << "Création Film " << film->titre << endl;

	for ([[maybe_unused]] auto i : range(nActeurs)) {  // On peut aussi mettre nElements avant et faire un span, comme on le faisait au TD précédent.
		film->acteurs.ajouter(lireActeur(fichier, listeFilms));
	}

	return film;
}

ListeFilms creerListe(string nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	
	int nElements = lireUint16(fichier);

	ListeFilms listeFilms;
	for ([[maybe_unused]] int i : range(nElements)) { //NOTE: On ne peut pas faire un span simple avec ListeFilms::enSpan car la liste est vide et on ajoute des éléments à mesure.
		listeFilms.ajouterFilm(lireFilm(fichier, listeFilms));
	}
	
	return listeFilms;
}

// Fonction pour détruire une ListeFilms et tous les films qu'elle contient.
//[
// On détruit sans détruire les films. On n'a pas demandé de refaire la lecture des films directement avec des pointeurs intelligents. On n'a pas demandé non plus de remplacer la méthode "detruire" par un destructeur.
void ListeFilms::detruire()
{
	//if (possedeLesFilms)  // Pas utile dans ce TD.
	//	for (Film* film : enSpan())
	//		delete film;
	delete[] elements;
}
//]

// Pour que l'affichage de Film fonctionne avec <<, il faut aussi modifier l'affichage de l'acteur pour avoir un ostream; l'énoncé ne demande pas que ce soit un opérateur, mais tant qu'à y être...
ostream& operator<< (ostream& os, const Acteur& acteur)
{
	return os << "  " << acteur.nom << ", " << acteur.anneeNaissance << " " << acteur.sexe << endl;
}

// Fonctions pour afficher les Item, Film, Livre ...
//[
ostream& operator<< (ostream& os, const Affichable& affichable)
{
	affichable.afficherSur(os);
	return os;
}

void Item::afficherSur(ostream& os) const
{
	os << "Titre: " << titre << "  Année:" << anneeSortie << endl;
}

void Film::afficherSpecifiqueSur(ostream& os) const
{
	os << "  Réalisateur: " << realisateur << endl;
	os << "  Recette: " << recette << "M$" << endl;
	os << "Acteurs:" << endl;
	for (auto&& acteur : acteurs.enSpan())
		os << *acteur;
}

void Film::afficherSur(ostream& os) const
{
	Item::afficherSur(os);
	Film::afficherSpecifiqueSur(os);
}

void Livre::afficherSpecifiqueSur(ostream& os) const
{
	os << "  Auteur: " << auteur << endl;
	os << "  Vendus: " << copiesVendues << "M  Pages: " << nPages << endl;
}

void Livre::afficherSur(ostream& os) const
{
	Item::afficherSur(os);
	Livre::afficherSpecifiqueSur(os);
}

void FilmLivre::afficherSur(ostream& os) const
{
	Item::afficherSur(os);
	os << "Combo:" << endl;
	// L'affichage comme l'exemple sur Discord est accepté, ici on montre comment on pourrait séparer en deux méthodes pour ne pas avoir le même titre d'Item affiché plusieurs fois.
	Film::afficherSpecifiqueSur(os);
	os << "Livre:" << endl;
	Livre::afficherSpecifiqueSur(os);
}

//]

// Pourrait être une méthode static pour construire un Livre à partir des données du fichier (pas encore vu les méthodes static dans le cours), ou un constructeur avec tag.  On a fait un constructeur explicit pour ne pas qu'un istream puisse est converti implicitement en livre, mais le tag n'était pas nécessaire puisqu'on avait une seule version de ce constructeur.  On a aussi décidé de faire une méthode pour lire (qui pourrait être utilisée par un opérateur, mais pas nécessaire ici).  La méthode pourrait être virtuelle si on avait besoin de faire la lecture selon le type dynamique mais ici on sais le type statiquement.
void Item::lireDe(istream& is)
{
	is >> quoted(titre) >> anneeSortie;
}
void Livre::lireDe(istream& is)
{
	Item::lireDe(is);
	is >> quoted(auteur) >> copiesVendues >> nPages;
}
Livre::Livre(istream& is) {
	lireDe(is);
}


template <typename T>
void afficherListeItems(T& listeItems)
{
	static const string ligneDeSeparation = "\033[32m────────────────────────────────────────\033[0m\n";
	cout << ligneDeSeparation;
	for (auto&& item : listeItems) {
		cout << *item << ligneDeSeparation;
	}
}


forward_list<shared_ptr<Item>> copierVecEnFList(vector<shared_ptr<Item>> items)
{
	forward_list<shared_ptr<Item>> flist;

	while(!items.empty())
	{	
		shared_ptr<Item> temp = items.back(); 
		flist.push_front(temp);
		items.pop_back();
	}
	return flist;
}


forward_list<shared_ptr<Item>> renverserFList(forward_list<shared_ptr<Item>> flist)
{
	forward_list<shared_ptr<Item>> flistRev;

	for (auto iterateur = flist.begin(); iterateur != flist.end(); iterateur++) 
	{
		flistRev.push_front(*iterateur);
	}
	return flistRev;
}

forward_list<shared_ptr<Item>> copierFList(forward_list<shared_ptr<Item>> flist)
{
	forward_list<shared_ptr<Item>> flistCop;
	auto posIt = flistCop.before_begin();
	for (auto iterateur = flist.begin(); iterateur != flist.end(); iterateur++) 
	{
		flistCop.insert_after(posIt,*iterateur);
		posIt++;
	}
	return flistCop;
}


vector<shared_ptr<Item>> renverserFListEnVec(forward_list<shared_ptr<Item>> flist)
{
	vector<shared_ptr<Item>> vect;
	for (auto iterateur = flist.begin(); iterateur != flist.end(); iterateur++) 
	{
		vect.insert(vect.begin(), *iterateur);
	}
	return vect;
}



#pragma region "Exemples de tests unitaires"//{
#ifdef TEST
// Pas demandés dans ce TD mais sert d'exemple.

TEST(tests_ListeFilms, tests_simples) {
	ListeFilms li;
	EXPECT_EQ(li.size(), 0);
	EXPECT_EQ(li.capacity(), 0);
	Film a, b, c;
	li.ajouterFilm(&a);
	li.ajouterFilm(&b);
	li.ajouterFilm(&c);
	EXPECT_EQ(li.size(), 3);
	EXPECT_GE(li.capacity(), 3);
	EXPECT_EQ(li[0], &a);
	EXPECT_EQ(li[1], &b);
	EXPECT_EQ(li[2], &c);
	li.detruire();
}

TEST(tests_ListeFilms, trouver) {
	ListeFilms li;
	Film films[3];
	string realisateurs[] = {"a","b","c","e"};
	for (auto&& [i,f] : enumerate(films)) {
		f.realisateur = realisateurs[i];
		li.ajouterFilm(&f);
	}
	for (auto&& [i,r] : enumerate(realisateurs)) {
		Film* film = li.trouver([&](const Film& f) { return f.realisateur == r; });
		// Le << après EXPECT_... permet d'afficher quelque chose en cas d'échec du test. Dans ce cas-ci, on veut savoir pour quel i ça a échoué.
		EXPECT_EQ(film, i < size(films) ? &films[i] : nullptr) << "  pour i=" << i;
	}
	li.detruire();
}

#endif
#pragma endregion//}


int main(int argc, char* argv[])
{
	initialiserBibliothequeCours(argc, argv);

	//int* fuite = new int; //TODO: Enlever cette ligne après avoir vérifié qu'il y a bien un "Detected memory leak" de "4 bytes" affiché dans la "Sortie", qui réfère à cette ligne du programme.

	static const string ligneDeSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";
	vector<shared_ptr<Item>> items;
	
	{
		ListeFilms listeFilms = creerListe("films.bin");
		for (auto&& film : listeFilms.enSpan())
			items.push_back(shared_ptr<Item>(film));  // On transert la possession.
		listeFilms.detruire();
	}

	{
		ifstream fichier("livres.txt");
		fichier.exceptions(ios::failbit);  // Pas demandé mais permet de savoir s'il y a une erreur de lecture.
		while (!ws(fichier).eof())
			items.push_back(make_shared<Livre>(fichier));
	}
	
	items.push_back(make_shared<FilmLivre>(dynamic_cast<Film&>(*items[4]), dynamic_cast<Livre&>(*items[9])));  // On ne demandait pas de faire une recherche; serait direct avec la matière du TD5.
	
	afficherListeItems(items);

	
	//1.1
	/*Copier les pointeurs du vecteur d’items final de la biliothèque dans une forward_list (liste liée simple
similaire à celle du chap.14) dans l’ordre original (même ordre que dans le vecteur), en O(n). Attention que
forward_list n’a pas de push_back*/
	forward_list<shared_ptr<Item>> flist = copierVecEnFList(items);
	afficherListeItems(flist);

	//1.2
	/*Copier la liste qui est en ordre original à l’envers (le dernier item se retrouve en premier) en O(n) dans une
autre forward_list sans passer par un conteneur intermédiaire ni avec une fonction récursive (fonction qui
fait appel à elle-même directement ou indirectement) ni en utilisant « reverse » qui le fait automatiquement. */
	forward_list<shared_ptr<Item>> flistrev = renverserFList(flist);
	afficherListeItems(flistrev);
	
	//1.3
	/*Copier la liste qui est en ordre original dans le même ordre qu’elle est, en O(n) dans une autre forward_list
sans passer par un conteneur intermédiaire ni avec une fonction récursive (fonction qui fait appel à ellemême directement 
ou indirectement) ni en utilisant la copie intégrée à forward_list (constructeur de copie
ou operator=)*/
	forward_list<shared_ptr<Item>> flistCop = copierFList(flist);
	afficherListeItems(flistCop);
	
	//1.4
	/*Copier la liste qui est en ordre original à l’envers dans un vector avec les mêmes contraintes que ci-dessus
(sans conteneur intermédiaire ni fonction récursive). Tentez d’optimiser l’ordre O(…) de votre algorithme
et indiquez cet ordre en commentaire.*/
	vector<shared_ptr<Item>> vect = renverserFListEnVec(flist); //O(n)
	afficherListeItems(vect);

	//1.5
	/*Ajoutez ce qu’il faut pour pouvoir itérer directement sur une liste : for (auto&& acteur : film.acteurs) (ou
film.getActeurs() si vous avez un accesseur qui retourne les ListeActeurs, pas un span qui a déjà ce qu’il
faut pour l’itérer de cette manière). Itérez en utilisant cette manière pour afficher les acteurs du premier
film (Alien) . */
	Film film = dynamic_cast<Film&>(*vect[0]);
	for (auto&& acteur : film.acteurs) {
		cout << acteur->nom<<endl;
	}
	cout << endl;

	//2.1
	/*Utilisez un conteneur, pas un algorithme de tri (pas « sort », « qsort » …), pour avoir les items en ordre
alphabétique. Affichez ces items. Encore, on utilise des pointeurs non propriétaires pour ne pas avoir à
faire de copies d’items tel que dit au début de l’énoncé. */
	map<string, shared_ptr<Item>> carte;
	for (int i : range(vect.size()))
	{
		carte[vect[i]->titre]=vect[i];
	}

	for (auto it=carte.begin();it!=carte.end();it++)
	{
		cout << it->first<<" ";
		cout << endl;
	}

	//2.2
	/*Utilisez un conteneur qui, après une étape initiale, va permettre de trouver des items par titre en O(1) en
moyenne pour chaque item cherché. Affichez l’item « The Hobbit ».*/
	unordered_map<string, shared_ptr<Item>> carteBrut;
	for (auto it = carte.begin(); it != carte.end(); it++)
	{
		carteBrut[it->first] = it->second;
	}
	cout<< carteBrut["The Hobbit"]<<endl;

	//3.1
	/*Utilisez l’algorithme copy_if ou copy pour copier les items qui « sont des » Film de liste faite en 1.1 vers un
vector, en gardant l’ordre, en une ligne de programme. Vous avez le droit d’écrire une fonction
d’adaptation, d’une ligne, qui permet de passer un « range » au lieu de deux itérateurs à ces algorithmes
(similairement à ce qu’il y a dans ranges:: de C++20).
Aide : vous pouvez commencer par écrire les différentes parties de la ligne sur plusieurs lignes pour aider à
trouver vos erreurs. 
*/
	vector<shared_ptr<Item>> v;
	copy_if(flist.begin(), flist.end(), back_inserter(v), [](shared_ptr<Item> i) {return dynamic_cast<Film*>(i.get())!=NULL; });
	cout << v[0]->titre << endl;

	//3.2
	/*Faites la somme des recettes des films trouvés ci-dessus, en une ligne (pas de « for »). 
	*/
	int somme =transform_reduce(v.begin(), v.end(), 0, plus{}, [](shared_ptr<Item> i) { return dynamic_cast<Film*>(i.get())->recette; });
	cout << somme;

	return 0;
}


class Tache {
public:
	Tache() {

	}

private:
	vector<Tache> taches_;
};

class Projet {
public:
	Projet() {
	}
	void ajouterTache(const Tache& tache);
	void supprimerTache(const Tache& tache);
	void supprimerTache(const Tache& tache);
	void trierTaches(function<bool(const Tache&, const Tache&)> f);

private:
	vector<Tache> taches_ ;
};

//Conteneur et algorithme :
void Projet::ajouterTache(const Tache& tache) {
	if (auto it = find(taches_.begin(), taches_.end(), tache); it == taches_.end())
		taches_.push_back(tache);
}

void Projet::supprimerTache(const Tache& tache) {
	auto it = remove(taches_.begin(), taches_.end(), tache);
	taches_.erase(it, taches_.end());
}
// Ou, puisque ce n'est pas dit s'il faut enlever plusieurs tâches identique (et n'est pas dans les tests):
void Projet::supprimerTache(const Tache& tache) {
	if (auto it = find(taches_.begin(), taches_.end(), tache); it != taches_.end())
		taches_.erase(it);
}

void Projet::trierTaches(function<bool(const Tache&, const Tache&)> f) {
	// Attention que le compilateur sur Moodle n'a pas les ranges:: de C++20.
	sort(taches_.begin(), taches_.end(), f);
}

/*
Questions en vrac :
Il est possible de lever une exception dans un bloc de capture d'exception ("catch"). 
; Il est possible d'utiliser plusieurs blocs "catch" à la suite d'un bloc "try".

L'utilisation d'un espace de noms(namespace) permet de * réduire * la portée(scope) 
de ce qu'elle contient. Il est possible de définir *un seule* symbole(s) ayant le même 
nom dans un même espace de nom.

doit absolument hériter de std::exception : Faux

Une méthode statique peut être appelée sans instancier d'objet de la classe dont elle 
fait partie. ; L'accès à une méthode statique peut se faire à l'aide de l'opérateur de 
résolution de portée("::").; L'utilisation d'attributs statiques de classe permet de les 
partager entre toutes les instances de la classe.

Exceptions:
13. Une exception est lancée dans Citoyen::faireDesCourses(), se propage à travers 
Citoyen::faireDesTartelettesPortugaises() et est attrapée dans le main().Le citoyen va 
ensuite attendre 14 jours(deuxième catch) et le programme se termine correctement(atteint 
la fin du main()).

14. Une exception est lancée dans Citoyen::faireDesCourses(), se propage à travers 
Citoyen::faireDesTartelettesPortugaises() et est attrapée dans le main().Le citoyen va 
ensuite garder ses distances et le programme se termine correctement(atteint la fin du main()).

15. Au premier appel de drArruda.faireDesTartelettesPortugaises(), une exception est 
levée et attrapée par le deuxième catch (donc on attend 14 jours).La boucle se répète une 
deuxième fois, la méthode complète son appel et affiche «Miam!», puis la boucle se brise.Le 
programme se termine ensuite normalement.
*/
