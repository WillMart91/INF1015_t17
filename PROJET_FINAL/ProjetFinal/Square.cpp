#include "Square.h"

Square::Square(int rank, int file)
{
	position = Position(rank, file);
	pieceOnMe = nullptr;
}

bool Square::friendlyOccupied(ChessPiece* piece)
{
	return piece->isBlackTeam()==pieceOnMe->isBlackTeam();
}
