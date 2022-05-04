
class Pawn : public AbsPiece
{
	Pawn(bool blackTeam, Square position, bool inStartPos = true);
	~Pawn() = default;
	virtual std::list<Square> getValidMoves();

private:
	const std::list<std::pair<int, int>> attMoves = { {1, 1},{-1, 1} };
	const std::pair<int, int> regMove = { 1, 0 };
	const std::pair<int, int> startMove = { 2, 0 };
};

