
#include "../../include/entities/BoardBase.h"

int BoardBase::GetBoardSize() const {
    return boardSize;
}

BoardBase::BoardBase(int boardSize) : boardSize(boardSize){}
