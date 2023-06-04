#include "../../include/helpers/MoveSimulator.hpp"
#include "../../include/helpers/BoardIndexConverter.hpp"
#include <algorithm>
#include <random>

std::array<Point, 2> MoveSimulator::SimulateMove(GameEngine *pEngine) {
  pEngine->GetBoardSize(); //TODO
  std::array<Point, 2> result;
  result[0] = Point(1, 1);
  result[1] = Point(1, 1);
  return result;
}

std::array<Point, 2> MoveSimulator::PerformRandomMove(
    std::vector<std::vector<Point>>& movesToChooseFrom,
                                                      unsigned int boardSize, int chosenSegment) {
  std::random_device rd;
  std::mt19937 gen(rd());
  unsigned int outerIndex;
  if(chosenSegment < 0)
  {
    std::uniform_int_distribution<> outerDist(0, movesToChooseFrom.size() - 1);
    outerIndex = outerDist(gen);
  }
  else
  {
    outerIndex = chosenSegment;
  }

  std::vector<Point> const& chosenVector = movesToChooseFrom[outerIndex];
  std::uniform_int_distribution<> innerDist(0, chosenVector.size() - 1);
  unsigned int innerIndex = innerDist(gen);
  Point chosenPoint = chosenVector[innerIndex];

  Point outerPoint = BoardIndexConverter::IndexToPoint(outerIndex, boardSize);

  std::array<Point, 2> result = { outerPoint, chosenPoint };
  return result;
}

//int MoveSimulator::minimax(Position position, int depth, bool maximizingPlayer) {
//  if (depth == 0 || game_over(position)) {
//    return evaluate(position);
//  }
//
//  if (maximizingPlayer) {
//    int maxEval = INT_MIN;
//    for (auto child : position.children()) {
//      int eval = minimax(child, depth - 1, false);
//      maxEval = std::max(maxEval, eval);
//    }
//    return maxEval;
//  } else {
//    int minEval = INT_MAX;
//    for (auto child : position.children()) {
//      int eval = minimax(child, depth - 1, true);
//      minEval = std::min(minEval, eval);
//    }
//    return minEval;
//  }
//}
