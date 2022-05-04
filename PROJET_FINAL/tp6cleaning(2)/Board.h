/*author: Gabriel Sawka and Wiliam Martin
* date: 25 april
* description: declaration of the chess board class. main class that manage all the flow of the game
*/

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
		AbsPiece* chessBoard[8][8];
	};
}
	


