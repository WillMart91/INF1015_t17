#pragma once
#include "AbsPiece.h"
#include "Square.h"
#include "King.h"
#include <vector>
namespace BackEnd {
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
		void addPiece(AbsPiece* piece, Square position);
	private:
		std::vector<std::vector<AbsPiece*>> chessBoard;

	};
}
	


