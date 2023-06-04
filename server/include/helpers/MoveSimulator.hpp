#ifndef ULTIMATETICTACTOESERVER_MOVESIMULATOR_H
#define ULTIMATETICTACTOESERVER_MOVESIMULATOR_H

#include "../entities/BoardBase.hpp"
#include "../gameengine/GameHandler.hpp"
#include <array>

class MoveSimulator {
public:
  static std::array<Point, 2> SimulateMove(GameEngine *pEngine);
  static std::array<Point, 2> PerformRandomMove
      (std::vector<std::vector<Point>>& movesToChooseFrom,
                                         unsigned int boardSize);

};

#endif // ULTIMATETICTACTOESERVER_MOVESIMULATOR_H
