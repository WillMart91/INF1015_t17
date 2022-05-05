#include "Pawn.h"
#include "Square.h"
#include "AbsPiece.h"
#include "Board.h"


Pawn::Pawn(bool blackTeam, Square position, bool inStartPos) :AbsPiece(blackTeam, position, inStartPos)
{
}

std::list<Square> Pawn::getValidMoves()
{
	Square pos = getSquare();
	std::list<Square> p;
	Square checkPos = regMove * ((-1)^ (int)isBlackTeam()) + pos;
	AbsPiece* pieceOn = Board::getInstance()->getPieceOn(checkPos);
	if (Square::isValid(checkPos) && pieceOn == nullptr)
	{
		p.push_back(checkPos);
	}
	checkPos = startMove * ((-1) ^ (int)isBlackTeam()) + pos;
	pieceOn = Board::getInstance()->getPieceOn(checkPos);
	if (inStartPos() && pieceOn == nullptr)
	{
		p.push_back(checkPos);
	}
	for (auto&& it = attMoves.begin(); it != attMoves.end(); it++) {
		checkPos = *it * ((-1) ^ (int)isBlackTeam()) + pos;
		pieceOn = Board::getInstance()->getPieceOn(checkPos);
		if (Square::isValid(checkPos) && pieceOn->isBlackTeam() != isBlackTeam())
		{
			p.push_back(checkPos);
		}
	}
	return p;
}
