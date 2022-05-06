#include "Board.h"
#include "PieceInclude.h"
#include <list>
#include <map>
#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

//TEST(Calc, simple) {
//	Calc calc;
//	calc.ajouterChiffre(1);
//	calc.ajouterChiffre(4);
//	calc.ajouterChiffre(3);
//	EXPECT_EQ(calc.obtenirValeur(), 143);
//	calc.effacer();
//	calc.ajouterChiffre(2);
//	calc.ajouterChiffre(1);
//	calc.ajouterChiffre(8);
//	EXPECT_EQ(calc.obtenirValeur(), 218);
//}

TEST(Board, layout) {
	std::map<Square, AbsPiece*> staleMate;
	staleMate[{ 5, 6 }] = new King(true, { 5,6 });
	staleMate[{ 7, 8 }] = new Queen(true, { 7,8 });

	staleMate[{ 3, 3 }] = new King(false, { 3,3 });
	Board::getInstance()->addLayout(staleMate);
	std::map<Square, AbsPiece*> a =Board::getInstance()->getLayout(1);
	std::map<Square, AbsPiece*> b = std::map<Square, AbsPiece*>();
	EXPECT_EQ(a, b);
	std::map<Square, AbsPiece*> c = Board::getInstance()->getLayout(0);
	EXPECT_EQ(c, staleMate);
	EXPECT_EQ(false, Board::getInstance()->isBlackTurn());
	Board::getInstance()->removeLayouts();
}

TEST(Board, validity_movement) {
	std::map<Square, AbsPiece*> staleMate = std::map<Square, AbsPiece*>();
	staleMate[{ 5, 6 }] = new King(true, { 5,6 });
	staleMate[{ 8, 8 }] = new Queen(true, { 8,8 });

	staleMate[{ 3, 3 }] = new King(false, { 3,3 });
	Board::getInstance()->addLayout(staleMate);
	Board::getInstance()->fillBoard(0);

	std::list<Square> e = Board::getInstance()->getMovesOfPiece({ 1,1 });
	std::list<Square> noMoves;
	EXPECT_EQ(e, noMoves);
	std::list<Square> a = Board::getInstance()->getMovesOfPiece({ 3,3 });
	std::list<Square> allMoves = { {4, 3},{2, 3},{3, 2},{3, 4}, {4, 4},{2, 4},{4, 2},{2, 2} };
	EXPECT_EQ(a, allMoves);
	std::pair<Square, Square> p ({ 3,3 }, { 3,3 });
	std::list<std::pair<Square, Square>> moves = { p };
	std::list<std::pair<Square, Square>> b = Board::getInstance()->moveOnBoard({ 5,7 });
	EXPECT_EQ(b, moves);
	std::list<std::pair<Square, Square>> c = Board::getInstance()->moveOnBoard({ 4,4 });
	EXPECT_EQ(c, moves);
	std::list<std::pair<Square, Square>> move = { std::make_pair<Square,Square>({3,3},{3,2}) };
	std::list<std::pair<Square, Square>> d = Board::getInstance()->moveOnBoard({ 3,2 });
	EXPECT_EQ(d, move);
	Board::getInstance()->removeLayouts();
}

//TEST(Board, move_pawn) {
//	std::map<Square, AbsPiece*> p;
//
//}

#endif