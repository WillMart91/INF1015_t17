/*
* Author: Gabriel Sawka and Wiliam Martin
* Date: mai  6 2022
* Description: This file has the purpose of testing multiples limit case in the backend portion the the game.
*/

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

TEST(Board, getmove_pawn) {
	std::map<Square, AbsPiece*> p;
	p[{ 1, 7 }] = new Pawn(false, { 1,7 });
	p[{ 3, 3 }] = new Pawn(false, { 3,3 });
	p[{ 2, 8 }] = new Pawn(true, { 2,8 });
	Board::getInstance()->addLayout(p);
	Board::getInstance()->fillBoard(0);

	std::list<Square> a = Board::getInstance()->getMovesOfPiece({ 1,7 });
	std::list<Square> aMoves = { {1,8},{2,8} };

	EXPECT_EQ(a, aMoves);
	std::list<Square> b = Board::getInstance()->getMovesOfPiece({ 3,3 });
	std::list<Square> bMoves = { {3,4},{3,5} };
	EXPECT_EQ(b, bMoves);
	Board::getInstance()->removeLayouts();
}
TEST(Board, getmove_bishop) {
	std::map<Square, AbsPiece*> p;
	p[{ 1, 1 }] = new Bishop(false, { 1,1 });
	p[{ 3, 3 }] = new Bishop(true, { 3,3 });
	Board::getInstance()->addLayout(p);
	Board::getInstance()->fillBoard(0);
	Board::getInstance()->removeLayouts();
	std::list<Square> a = Board::getInstance()->getMovesOfPiece({ 1,1 });
	std::list<Square> allMoves = { {2,2},{3,3} };
	EXPECT_EQ(a, allMoves);
	Board::getInstance()->removeLayouts();
}
TEST(Board, getmove_queen) {
	std::map<Square, AbsPiece*> p;
	p[{ 1, 1 }] = new Queen(false, { 1,1 });
	p[{ 1, 4 }] = new Queen(true, { 1,4 });
	p[{ 3, 3 }] = new Knight(false, { 3,3 });
	p[{ 2, 1 }] = new Rook(false, { 2,1 });
	Board::getInstance()->addLayout(p);
	Board::getInstance()->fillBoard(0);
	Board::getInstance()->removeLayouts();
	std::list<Square> a = Board::getInstance()->getMovesOfPiece({ 1,1 });
	std::list<Square> allMoves = { {1,2},{2,2},{1,3},{1,4} };
	EXPECT_EQ(a, allMoves);
	Board::getInstance()->removeLayouts();
}
TEST(Board, getmove_rook) {
	std::map<Square, AbsPiece*> p;
	p[{ 1, 1 }] = new Rook(false, { 1,1 });
	p[{ 1, 3 }] = new Rook(true, { 1,3 });
	p[{ 3, 1 }] = new Rook(true, { 3,1 });
	Board::getInstance()->addLayout(p);
	Board::getInstance()->fillBoard(0);
	Board::getInstance()->removeLayouts();
	std::list<Square> a = Board::getInstance()->getMovesOfPiece({ 1,1 });
	std::list<Square> allMoves = { {2,1},{1,2},{3,1},{1,3} };
	EXPECT_EQ(a, allMoves);
	Board::getInstance()->removeLayouts();
}
TEST(Board, getmove_knight) {
	std::map<Square, AbsPiece*> p;
	p[{ 2, 2 }] = new Knight(false, { 2,2 });
	p[{ 4, 3 }] = new Pawn(true, { 4,3 });
	Board::getInstance()->addLayout(p);
	Board::getInstance()->fillBoard(0);
	Board::getInstance()->removeLayouts();
	std::list<Square> a = Board::getInstance()->getMovesOfPiece({ 2,2 });
	std::list<Square> allMoves = { {4, 3},{4, 1},{3,4},{1,4}};
	EXPECT_EQ(a, allMoves);
	Board::getInstance()->removeLayouts();
}
TEST(Board, getmove_king) {
	std::map<Square, AbsPiece*> p;
	p[{ 1, 1 }] = new King(false, { 1,1 });
	p[{ 1, 2 }] = new Pawn(true, { 1,2 });
	Board::getInstance()->addLayout(p);
	Board::getInstance()->fillBoard(0);
	Board::getInstance()->removeLayouts();
	std::list<Square> a = Board::getInstance()->getMovesOfPiece({ 1,1 });
	std::list<Square> allMoves = { {2, 1},{1, 2}, {2,2} };
	EXPECT_EQ(a, allMoves);
	Board::getInstance()->removeLayouts();
}
TEST(Board, check) {
	std::map<Square, AbsPiece*> p;
	p[{ 4, 4 }] = new King(false, { 4,4 });
	p[{ 1, 4 }] = new Pawn(false, { 1,4 });
	p[{ 1, 1 }] = new Queen(true, { 1,1 });
	p[{ 8, 8 }] = new Bishop(true, { 8,8 });
	p[{ 4, 8 }] = new Rook(true, { 4,8 });
	p[{ 3, 5 }] = new Pawn(true, { 3,5 });
	p[{ 6, 3 }] = new Knight(true, { 6,3 });
	Board::getInstance()->addLayout(p);
	Board::getInstance()->fillBoard(0);
	std::list<Square> a = Board::getInstance()->getMovesOfPiece({ 1,4 });
	std::list<std::pair<Square, Square>> move = { std::make_pair<Square,Square>({1,4},{1,4}) };
	std::list<std::pair<Square, Square>> d = Board::getInstance()->moveOnBoard({ 1,5 });
	EXPECT_EQ(d, move);
	Board::getInstance()->removeLayouts();
}


TEST(Board, destructors) {

	
	King* king = new King(false, { 1,1 });
	delete(king);

	Queen* q = new Queen(false, { 2,2 });
	delete(q);

	Knight* k = new Knight(false, { 3,3 });
	delete(k);

	Rook* r = new Rook(false, { 4,4 });
	delete(r);

	Bishop* b = new Bishop(false, { 5,5 });
	delete(b);
	Pawn* p = new Pawn(false, { 6,6 });
	delete(p);

	Board::getInstance()->~Board();
}


TEST(Square, operators) {

	Square s1 = { 1,1 };
	Square s2 = { 2,2 };
	Square s4 = { 3,3 };
	Square s3 = s1 + s2;
	bool s = s3 == s4;
	EXPECT_EQ(s, true);

	std::pair<int,int> p1(2,2);
	std::pair<int, int> p2(4, 4);
	p1 = 2 * p1;
	
	EXPECT_EQ(p1, p2);

}


#endif