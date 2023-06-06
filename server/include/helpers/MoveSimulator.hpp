#ifndef ULTIMATETICTACTOESERVER_MOVESIMULATOR_H
#define ULTIMATETICTACTOESERVER_MOVESIMULATOR_H

#include "../entities/BoardBase.hpp"
#include "../gameengine/GameHandler.hpp"
#include <array>

/*  Class: MoveSimulator
    Static class responsible for simulating and choosing move of the
    computer player
*/
class MoveSimulator {
public:
  /*  Function: PerformRandomMove

  Performs random move from available moves using heuristics.

      Parameters:

      movesToChooseFrom - 2d vector of points, first vector indicates segment of
      main board (index) and the second vector the available moves inside
  segment. boardSize - size of tic-tac-toe board. chosenSegment - currently
  played segment (inner board)

      Returns:

      Array of coordinates where move should be done. First element is Point of
      outer board and second is the point of inner board

      See Also:

      <Point>
          */
  static std::array<Point, 2>
  PerformRandomMove(std::vector<std::vector<Point>> &movesToChooseFrom,
                    unsigned int boardSize, int chosenSegment);
};

#endif // ULTIMATETICTACTOESERVER_MOVESIMULATOR_H
