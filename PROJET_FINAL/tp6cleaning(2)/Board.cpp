/*author: Gabriel Sawka and Wiliam Martin
* date: 25 april
* description: part implementation of the chess board
*/


#include "Board.h"
#include <stdexcept>
#include <iostream>
namespace BackEnd {
	Board::Board()
	{
		fillBoard();
	}
	Board::~Board()
	{
		for (int i = 0; i < 8; i++) {
			for (int j = 0; i < 8; j++) {
				delete chessBoard[i][j];
			}
		}
	}
	void Board::movePiece(AbsPiece* piece, Square moveTo)
	{
	}
	void Board::fillBoard()
	{
		King* k=nullptr;
		try {
			k =new King(true, Square{ 0,0 });
			chessBoard[0][0] = k;
		}
		catch(std::logic_error& e) {
			chessBoard[0][0] = nullptr;
			std::cout << "error resolved"<< e.what();
			delete k;
		}

	}
	void Board::tryMove(AbsPiece* piece, Square moveTo)
	{
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
	void Board::addPiece(AbsPiece* piece, Square position)
	{
	}
}


