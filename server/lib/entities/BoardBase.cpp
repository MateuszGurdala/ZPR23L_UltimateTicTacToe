
#include "../../include/entities/BoardBase.hpp"

int BoardBase::GetBoardSize() const {
    return boardSize;
}

BoardBase::BoardBase(int boardSize) : boardSize(boardSize){}

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
