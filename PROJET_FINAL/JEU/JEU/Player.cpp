#include "Player.h"

AbsPiece* Player::getPieceOn(Square pos)
{
    for (int p = 0; p < piecesAlive.size(); p++) {
        Square posPiece = piecesAlive[p]->getPosition();
        if ((posPiece.file == pos.file) & (posPiece.rank == pos.rank)) {
            return piecesAlive[p];
        }
    }
    return nullptr;
}


bool Player::isFriendly(AbsPiece* piece)
{
    for (int p = 0; p < piecesAlive.size(); p++) {
        if (piecesAlive[p]==piece) {
            return true;
        }
    }
    return false;
}
