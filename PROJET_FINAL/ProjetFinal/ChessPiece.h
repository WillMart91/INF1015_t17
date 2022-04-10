#pragma once
#include "Position.h"

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class ChessPiece : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT
public:
	ChessPiece();
	virtual Position calculateMoves() = 0;

};

