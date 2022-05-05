#include <list>
struct Square;
class King : public AbsPiece
{
public:
	King(bool blackTeam, Square position, bool inStartPos = true);
	~King();
	std::list<Square> getValidMoves();
	bool isChecked();
private:
	static int nbOfKings;
	const std::list<std::pair<int, int>> allMoves = { {1, 0},{-1, 0},{0, -1},{0, 1}, {1, 1},{-1, 1},{1, -1},{-1, -1} };

	const std::list<std::pair<int, int>> knightCheck = { {2, 1},{-2, 1},{2, -1},{-2, -1},{1,2},{-1,2}, {1,-2},{-1,-2} };
	const std::list<std::pair<int, int>> bishopCheck = { {1, 1},{-1, 1},{1, -1},{-1, -1} };
	const std::list<std::pair<int, int>> rookCheck = { {1, 0},{-1, 0},{0, -1},{0, 1} };
	const std::list<std::pair<int, int>> pawnCheck = { {1, 1},{-1, 1} };
};

