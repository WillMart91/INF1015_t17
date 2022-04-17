#pragma once
#include "AbsPiece.h"
#include "Square.h"
#include <vector>

class Board
{
public:
	Board();
	~Board();
	void movePiece(AbsPiece* piece, Square moveTo);
	void fillBoard();//ou   void startGame();				//semi ctor
	void tryMove(AbsPiece* piece, Square moveTo);
	//std::vector<Square> validateMoves(std::vector<Square> moveList);
	void getMoves(Square position); //pt
	friend AbsPiece;
private:
	std::vector<std::vector<AbsPiece*>> chessBoard;

};

