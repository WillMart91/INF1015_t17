#pragma once
#include "AbsPiece.h"
#include "Square.h"
#include <vector>

class Player
{
public:
	Player();
	~Player();
	AbsPiece* getPieceOn(Square pos);
	void deadPiece(AbsPiece* piece);
	bool isFriendly(AbsPiece* piece);
private:
	std::vector<AbsPiece*> piecesAlive;
	std::vector<AbsPiece*> piecesDead;
};

