#include "Board.h"

void Board::getMoves(Square position)
{
	AbsPiece* piece = chessBoard[position.file][position.rank];
	if (piece == nullptr) {
		return;
	}
	//std::vector<Square> moveList = validateMoves(piece->getMoves());
	Square startPos = piece->getPosition();

}
