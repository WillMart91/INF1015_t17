#include "Position.h"

Position operator+(const Position p1, const Position p2)
{
	return Position(p1.rank+p2.rank,p1.file+p2.file);
}
Position operator-(const Position p1, const Position p2)
{
	return Position(p1.rank - p2.rank, p1.file - p2.file);
}
