#ifndef ULTIMATETICTACTOESERVER_BOARDINDEXCONVERTER_HPP
#define ULTIMATETICTACTOESERVER_BOARDINDEXCONVERTER_HPP

#include "../entities/BoardBase.hpp"

/*  Class: BoardIndexConverter
    Helper class used for converting (x,y) coordinates used by server to one
   index which is supported by client
*/
class BoardIndexConverter {
public:
  /*  Function: pointToIndex

  Converts Point on cartesian board (x,y) to index.

  Parameters:

    point - struct containing positive integer coordinates x and y.
    boardSize - size of tic-tac-toe board.

   Returns:

    Index of client's game board.

  See Also:

    <Point>
*/
  static int pointToIndex(Point &point, unsigned int &boardSize);

  /*  Function: handleGETRequest

  Converts index to Point on cartesian board (x,y) .

  Parameters:

    index - Index of board cell. Index starts at 0.
    boardSize - size of tic-tac toe-board.

  Returns:

    Struct containing positive integer coordinates x and y which is
    compatible with server

  See Also:

    <Point>
*/
  static Point indexToPoint(unsigned int &index, unsigned int &boardSize);
};

#endif // ULTIMATETICTACTOESERVER_BOARDINDEXCONVERTER_HPP
