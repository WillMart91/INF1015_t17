#include "Board.h"
class Pawn : public AbsPiece
{
public:
	Pawn(bool blackTeam, Square position, bool inStartPos = true);
	~Pawn() = default;
	virtual std::list<Square> getValidMoves();

private:
	const std::list<std::pair<int, int>> attMoves = { {1, 1},{-1, 1} };
	const std::pair<int, int> regMove = { 0, 1 };
	const std::pair<int, int> startMove = { 0, 2 };
};

