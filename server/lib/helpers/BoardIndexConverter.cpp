#include "../../include/helpers/BoardIndexConverter.hpp"

int BoardIndexConverter::PointToIndex(Point &point, unsigned int &boardSize) {
  if (boardSize <= 0) {
    throw std::invalid_argument("Size of board must be positive");
  }
  return point.x * boardSize + point.y;
}

Point BoardIndexConverter::IndexToPoint(unsigned int &index,
                                        unsigned int &boardSize) {
  if (boardSize <= 0) {
    throw std::invalid_argument("Size of board must be positive");
  }
  unsigned int y = index % boardSize;
  unsigned int x = (index - y) / boardSize;
  auto point = Point(x, y);
  return point;
}
