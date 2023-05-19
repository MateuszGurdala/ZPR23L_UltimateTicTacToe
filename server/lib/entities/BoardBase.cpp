
#include "../../include/entities/BoardBase.hpp"

unsigned int BoardBase::GetBoardSize() const {
    return boardSize;
}

BoardBase::BoardBase(unsigned int boardSize) : boardSize(boardSize){

    if(boardSize <= 0)
    {
        throw std::invalid_argument("size of board must be positive");
    }
}

void BoardBase::VerifyFigure(char figure) {
    if(figure != 'X' && figure != 'O')
    {
        throw std::invalid_argument("only allowed figures are X and O");
    }
}

void BoardBase::VerifyCoordinates(Point coordinates) const {
    if(coordinates.x < 0 || coordinates.x >= boardSize || coordinates.y < 0 || coordinates.y >= boardSize)
    {
        throw std::out_of_range("Coordinates are out of bounds of board");
    }
}
