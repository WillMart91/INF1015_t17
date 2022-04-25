#pragma once
#include "AbsPiece.h"
class Pawn: AbsPiece
{
public:
	Pawn(bool blackTeam, Square beginPos);
	virtual std::vector<Square> getValidPositions(const std::vector<std::vector<AbsPiece*>> chessBoard);
	//AbsPiece* endSwitch();
private:


	const int range =1;
	const std::vector<std::pair<int, int>> direction = { {1, 0} };
	const std::vector<std::pair<int, int>> attackDirection = { {1, 1}, {1,-1} };
	
};

