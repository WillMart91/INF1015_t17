#pragma once
#include "AbsPiece.h"
class knight : AbsPiece
{
public:
	knight(bool blackTeam, Square beginPos);
	virtual std::vector<Square> getValidPositions(const std::vector<std::vector<AbsPiece*>> chessBoard);
	//AbsPiece* endSwitch();

private:
	const std::vector<std::vector<int, int>> direction = { {2, 1},{-2, 1},{2, -1},{-2, -1},{1,2},{-1,2}, {1,-2},{-1,-2} };
	

};