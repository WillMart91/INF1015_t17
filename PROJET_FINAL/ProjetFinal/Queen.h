/*
* Author: Gabriel Sawka and Wiliam Martin
* Date: mai  6 2022
* Description: A Queen is the definition of a simple type of chess piece
*/

#include "Board.h"
class Queen : public AbsPiece
{
public:
	Queen(bool blackTeam, Square position, bool inStartPos = true);
	~Queen() = default;
	virtual std::list<Square> getValidMoves();

private:
	const std::list<std::pair<int, int>> allDir = { {1, 0},{-1, 0},{0, -1},{0, 1}, {1, 1},{-1, 1},{1, -1},{-1, -1} };

};

