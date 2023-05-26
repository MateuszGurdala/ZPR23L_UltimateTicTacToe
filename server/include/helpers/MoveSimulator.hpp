#ifndef ULTIMATETICTACTOESERVER_MOVESIMULATOR_H
#define ULTIMATETICTACTOESERVER_MOVESIMULATOR_H

#include "../entities/BoardBase.hpp"
#include "../gameengine/GameHandler.hpp"
#include <array>

class MoveSimulator {
public:
  static std::array<Point, 2> simulateMove(GameHandler& gameHandler, int depth);
}

#endif // ULTIMATETICTACTOESERVER_MOVESIMULATOR_H
