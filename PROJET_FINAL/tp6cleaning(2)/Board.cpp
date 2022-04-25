#include "Board.h"
#include <stdexcept>
#include <iostream>
namespace BackEnd {
	void Board::fillBoard()
	{
		King* k=nullptr;
		try {
			k =new King(true, Square{ 0,0 });
			chessBoard[0][0] = k;
		}
		catch(std::logic_error& e) {
			chessBoard[0][0] = nullptr;
			std::cout << "error resolved";
			delete k;
		}

	}
	void Board::getMoves(Square position)
	{
		AbsPiece* piece = chessBoard[position.file][position.rank];
		if (piece == nullptr) {
			return;
		}
		//std::vector<Square> moveList = validateMoves(piece->getMoves());
		Square startPos = piece->getPosition();

	}
}


