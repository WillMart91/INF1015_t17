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

