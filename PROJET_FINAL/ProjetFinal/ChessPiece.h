#pragma once
#include "Position.h"
#include "Board.h"

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

#include <vector>

class ChessPiece : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT
public:
	virtual void calculateMoves(Board* board) = 0;
	virtual std::vector<Position> getPossibleMoves();
	bool isBlackTeam() { return isBlack; }

private :
	bool isBlack;

	std::vector<Position> movesList;
	const std::vector<std::vector<int, int>> direction;
};

