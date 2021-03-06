#include <vector>
#include <list>
#include "Board.h"
class King : public AbsPiece
{
public:
	King(bool blackTeam, Square position, bool inStartPos = true);
	~King();
	std::list<Square> getValidMoves();
private:
	static int nbOfKings;
	const std::list<std::pair<int, int>> allMoves = { {1, 0},{-1, 0},{0, -1},{0, 1}, {1, 1},{-1, 1},{1, -1},{-1, -1} };
};

