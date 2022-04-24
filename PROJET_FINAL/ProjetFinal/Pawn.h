#include "AbsPiece.h"

class Pawn : public AbsPiece
{
public:
	Pawn(bool blackTeam, Position beginPos, QGraphicsItem* parent);
};
