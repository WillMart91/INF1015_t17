/*
* Author: Gabriel Sawka and Wiliam Martin
* Date: mai  6 2022
* Description: A Bishop is the definition of a simple type of chess piece
*/

#include "Board.h"
class Bishop : public AbsPiece
{
public:
	Bishop(bool blackTeam, Square position, bool inStartPos = true);
	~Bishop() = default;
	virtual std::list<Square> getValidMoves();

private:
	const std::list<std::pair<int, int>> allDir = { {1, 1},{-1, 1},{1, -1},{-1, -1} };
};


