#include <vector>
struct Square
{
	int file;
	int rank;
	static bool isValid(Square s);
};
Square operator+(const Square p1, const Square p2);
Square operator+(const Square p1, const std::pair<int, int> move);
Square operator+(const std::pair<int, int> move, const Square p1);
std::pair<int, int> operator*(const std::pair<int, int> move, const int i);
std::pair<int, int> operator*(const int i, const std::pair<int, int> move);
bool operator==(const Square p1, const Square p2);
bool operator<(const Square p1, const Square p2);
