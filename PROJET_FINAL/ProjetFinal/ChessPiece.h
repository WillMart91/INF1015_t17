#pragma once
#include "Position.h"

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

#include <vector>

class ChessPiece : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT
public:
	ChessPiece();
	virtual std::vector<Position> calculateMoves() = 0;

};

