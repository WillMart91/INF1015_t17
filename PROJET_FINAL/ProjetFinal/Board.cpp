#include "Board.h"

#include "King.h"

#include "AbsPiece.h"
#include "Square.h"

Board::~Board()
{
    for (auto&& it = chessBoard_.begin(); it != chessBoard_.end(); it++) {
        delete it->second;
    }
}

std::list<Square> Board::getMovesOfPiece(Square clicked)
{
    std::list<Square> moves;
    lastClicked = clicked;
    AbsPiece* piece = chessBoard_[clicked];
    if (piece != nullptr) {
        if (piece->isBlackTeam() == blackTurn) {
            moves = piece->getValidMoves();
        }
    }
    return moves;
}

std::list<std::pair<Square, Square>> Board::moveOnBoard(Square clicked)
{
    std::map<Square, AbsPiece*> chessBoardBefore = chessBoard_;
    chessBoard_[clicked] = chessBoard_[lastClicked];
    chessBoard_.erase(lastClicked);
    bool danger=false;
    for (auto&& it = chessBoard_.begin(); it != chessBoard_.end(); it++) {
        King* k = dynamic_cast<King*>(it->second);
        if (k != nullptr) {
            if (k->isBlackTeam() == blackTurn) {
                danger= k->isChecked();
                break;
            }
        }
    }
    std::list<std::pair<Square, Square>> moves;
    if (!danger) {
        moves.push_back({ lastClicked, clicked });
        blackTurn = !blackTurn;
    }
    else {
        moves.push_back({ lastClicked, lastClicked });
        chessBoard_ = chessBoardBefore;
    }
    return moves;
}

