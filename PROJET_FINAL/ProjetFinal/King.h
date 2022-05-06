/*
* Author: Gabriel Sawka and Wiliam Martin
* Date: mai  6 2022
* Description: A King is the definition of a simple type of chess piece
*/

#include <vector>
#include <list>
#include "Board.h"
class King : public AbsPiece
{
public:
	King(bool blackTeam, Square position, bool inStartPos = true);
	~King()=default;
	std::list<Square> getValidMoves();
private:
	const std::list<std::pair<int, int>> allMoves = { {1, 0},{-1, 0},{0, -1},{0, 1}, {1, 1},{-1, 1},{1, -1},{-1, -1} };
};

