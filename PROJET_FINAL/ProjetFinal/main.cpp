#pragma once

#include "Calc.hpp"
#include "CalcWindow.hpp"
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
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette ent�te si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.
#endif

void initialiserBibliothequeCours([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	#ifdef BIBLIOTHEQUE_COURS_INCLUS
	bibliotheque_cours::activerCouleursAnsi();  // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par d�faut. // cdbg.setTee(&clog);  // D�commenter cette ligne pour que cdbg affiche sur la console en plus de la "Sortie" du d�bogueur.
	bibliotheque_cours::executerGoogleTest(argc, argv); // Attention de ne rien afficher avant cette ligne, sinon l'Explorateur de tests va tenter de lire votre affichage comme un r�sultat de test.
	#endif //NOTE: C'est normal que la couverture de code dans l'Explorateur de tests de Visual Studio ne couvre pas la fin de cette fonction ni la fin du main apr�s l'appel � cette fonction puisqu'il ex�cute uniquement les tests Google Test dans l'appel ci-dessus.
}

//using namespace FrontEnd;

int main(int argc, char *argv[])
{

	bibliotheque_cours::VerifierFuitesAllocations verifierFuitesAllocations;
	QApplication app(argc, argv);
	std::map<Square, AbsPiece*> b;

	for (int i = 1; i <= 8; i++) {
		b[{ i,2 }]=new Pawn(true, { i,2 });
	}
	b[{ 1,1 }]=new Rook(true, { 1,1 });
	b[{ 8,1 }]=new Rook(true, { 8,1 });
	b[{ 2,1 }]=new Knight(true, { 2,1 });
	b[{ 7,1 }]=new Knight(true, { 7,1 });
	b[{ 3,1 }]=new Bishop(true, { 3,1 });
	b[{ 6,1 }]=new Bishop(true, { 6,1 });
	b[{ 5,1 }]=new King(true, { 5,1 });
	b[{ 4,1 }]=new Queen(true, { 4,1 });

	for (int i = 1; i <= 8; i++) {
		b[{ i,7 }]=new Pawn(false, { i,7 });
	}
	b[{ 1,8 }]=new Rook(false, { 1,8 });
	b[{ 8,8 }]=new Rook(false, { 8,8 });
	b[{ 2,8 }]=new Knight(false, { 2,8 });
	b[{ 7,8 }]=new Knight(false, { 7,8 });
	b[{ 3,8 }]=new Bishop(false, { 3,8 });
	b[{ 6,8 }]=new Bishop(false, { 6,8 });
	b[{ 5,8 }]=new King(false, { 5,8 });
	b[{ 4,8 }]=new Queen(false, { 4,8 });

	Board::getInstance()->fillBoard(b);

	FrontEnd::Game game;

	initialiserBibliothequeCours(argc, argv);
	return app.exec();

}




