/*
* Author: Gabriel Sawka and Wiliam Martin
* Date: mai  6 2022
* Description: A knight is the definition of a simple type of chess piece
*/

#include "Board.h"
class Knight : public AbsPiece
{
public:
	Knight(bool blackTeam, Square position, bool inStartPos = true);
	~Knight() = default;
	std::list<Square> getValidMoves();

private:
	const std::list<std::pair<int,int>> allMoves = { {2, 1},{-2, 1},{2, -1},{-2, -1},{1,2},{-1,2}, {1,-2},{-1,-2} };
};

