
class Rook : public AbsPiece
{
public:
	Rook(bool blackTeam, Square position, bool inStartPos = true);
	~Rook() = default;
	virtual std::list<Square> getValidMoves();

private:
	const std::list<std::pair<int, int>> allDir = { {1, 0},{-1, 0},{0, -1},{0, 1} };

};

