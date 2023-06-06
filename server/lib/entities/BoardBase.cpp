
#include "../../include/entities/BoardBase.hpp"
#include <vector>

unsigned int BoardBase::getBoardSize() const { return boardSize; }

BoardBase::BoardBase(unsigned int boardSize) : boardSize(boardSize) {

  if (boardSize <= 0) {
    throw std::invalid_argument("size of board must be positive");
  }
}

void BoardBase::verifyFigure(char figure) {
  if (figure != 'X' && figure != 'O') {
    throw std::invalid_argument("only allowed figures are X and O");
  }
}

void BoardBase::verifyCoordinates(Point point) const {
  if (point.x >= boardSize || point.y >= boardSize) {
    throw std::out_of_range("Coordinates are out of bounds of board");
  }
}
