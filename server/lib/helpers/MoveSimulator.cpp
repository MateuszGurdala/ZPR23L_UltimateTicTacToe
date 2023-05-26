
#include "../../include/helpers/MoveSimulator.hpp"

std::array<Point, 2> MoveSimulator::simulateMove(GameHandler &gameHandler, int depth) {
  std::array<Point, 2> result;
  result[0] = Point(1, 1);
  result[1] = Point(1, 1);
  return result;
}
