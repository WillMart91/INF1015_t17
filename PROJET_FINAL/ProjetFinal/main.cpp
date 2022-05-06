
#pragma once
#include "Game.h"
#include "PieceInclude.h"
#include "AbsPiece.h"
#include <map>
#include <list>
#include <QApplication>


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
	bibliotheque_cours::activerCouleursAnsi();  // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par défaut. // cdbg.setTee(&clog);  // Décommenter cette ligne pour que cdbg affiche sur la console en plus de la "Sortie" du débogueur.
	bibliotheque_cours::executerGoogleTest(argc, argv); // Attention de ne rien afficher avant cette ligne, sinon l'Explorateur de tests va tenter de lire votre affichage comme un résultat de test.
	#endif //NOTE: C'est normal que la couverture de code dans l'Explorateur de tests de Visual Studio ne couvre pas la fin de cette fonction ni la fin du main après l'appel à cette fonction puisqu'il exécute uniquement les tests Google Test dans l'appel ci-dessus.
}

//using namespace FrontEnd;
void setUpLayouts();
int main(int argc, char *argv[])
{

	bibliotheque_cours::VerifierFuitesAllocations verifierFuitesAllocations;
	QApplication app(argc, argv);
	initialiserBibliothequeCours(argc, argv);

	setUpLayouts();

	FrontEnd::Game game;

	
	return app.exec();
}




void setUpLayouts() {
	std::map<Square, AbsPiece*> classic;

	for (int i = 1; i <= 8; i++) {
		classic[{ i, 2 }] = new Pawn(false, { i,2 });
	}
	classic[{ 1, 1 }] = new Rook(false, { 1,1 });
	classic[{ 8, 1 }] = new Rook(false, { 8,1 });
	classic[{ 2, 1 }] = new Knight(false, { 2,1 });
	classic[{ 7, 1 }] = new Knight(false, { 7,1 });
	classic[{ 3, 1 }] = new Bishop(false, { 3,1 });
	classic[{ 6, 1 }] = new Bishop(false, { 6,1 });
	classic[{ 5, 1 }] = new King(false, { 5,1 });
	classic[{ 4, 1 }] = new Queen(false, { 4,1 });

	for (int i = 1; i <= 8; i++) {
		classic[{ i, 7 }] = new Pawn(true, { i,7 });
	}
	classic[{ 1, 8 }] = new Rook(true, { 1,8 });
	classic[{ 8, 8 }] = new Rook(true, { 8,8 });
	classic[{ 2, 8 }] = new Knight(true, { 2,8 });
	classic[{ 7, 8 }] = new Knight(true, { 7,8 });
	classic[{ 3, 8 }] = new Bishop(true, { 3,8 });
	classic[{ 6, 8 }] = new Bishop(true, { 6,8 });
	classic[{ 5, 8 }] = new King(true, { 5,8 });
	classic[{ 4, 8 }] = new Queen(true, { 4,8 });
	Board::getInstance()->addLayout(classic);

	std::map<Square, AbsPiece*> trios;
	trios[{ 3, 8 }] = new King(true, { 3, 8 });
	trios[{ 8, 6 }] = new Queen(true, { 8,6 });
	trios[{ 3, 5 }] = new Knight(true, { 3,5 });


	trios[{ 6, 2 }] = new King(false, { 6,2 });
	trios[{ 5, 1 }] = new Rook(false, { 5,1 });
	trios[{ 3, 4 }] = new Bishop(false, { 3,4 });
	Board::getInstance()->addLayout(trios);

	std::map<Square, AbsPiece*> staleMate;
	staleMate[{ 5, 6 }] = new King(true, { 5,6 });
	staleMate[{ 7, 8 }] = new Queen(true, { 7,8 });

	staleMate[{ 3, 3 }] = new King(false, { 3,3 });
	Board::getInstance()->addLayout(staleMate);

}