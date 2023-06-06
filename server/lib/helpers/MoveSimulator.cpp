#include "../../include/helpers/MoveSimulator.hpp"
#include "../../include/helpers/BoardIndexConverter.hpp"
#include <algorithm>
#include <chrono>
#include <random>
#include <thread>

std::array<Point, 2> MoveSimulator::performRandomMove(
    std::vector<std::vector<Point>> &movesToChooseFrom, unsigned int boardSize,
    int chosenSegment) {
  std::random_device rd;
  std::mt19937 gen(rd());
  unsigned int outerIndex;
  if (chosenSegment < 0) {
    std::vector<unsigned int> validIndices;
    for (unsigned int i = 0; i < movesToChooseFrom.size(); ++i) {
      if (!movesToChooseFrom[i].empty()) {
        validIndices.push_back(i);
      }
    }

    if (validIndices.empty()) {
      throw std::runtime_error("No valid moves available.");
    }

    std::uniform_int_distribution<> outerDist(0, validIndices.size() - 1);
    outerIndex = validIndices[outerDist(gen)];
  } else {
    outerIndex = chosenSegment;
  }

  std::vector<Point> const &chosenVector = movesToChooseFrom[outerIndex];
  std::uniform_int_distribution<> innerDist(0, chosenVector.size() - 1);
  unsigned int innerIndex = innerDist(gen);
  Point chosenPoint = chosenVector[innerIndex];

  Point outerPoint = BoardIndexConverter::indexToPoint(outerIndex, boardSize);

  std::array<Point, 2> result = {outerPoint, chosenPoint};
  std::this_thread::sleep_for(std::chrono::seconds(1));
  return result;
}