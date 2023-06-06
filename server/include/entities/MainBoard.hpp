#ifndef ULTIMATETICTACTOESERVER_MAINBOARD_HPP
#define ULTIMATETICTACTOESERVER_MAINBOARD_HPP

#include "InnerBoard.hpp"
#include <vector>

/*  Class: MainBoard
        Outer board of the game which includes 2d vector of InnerBoards. Also
   has helper array called winnerBoard which stores information who won specific
   inner board.

        see also:
        <InnerBoard>
 */
class MainBoard : public BoardBase {
private:
  std::vector<std::vector<std::unique_ptr<InnerBoard>>> mainPlayBoard;
  std::unique_ptr<InnerBoard> winnerBoard;
  /*  Function: FillBoard
  Fills main play board with InnerBoard objects and winner board with
  whitespaces.
   */
  void FillBoard() override;

public:
  /*  Constructor: MainBoard
  Constructor which takes size of board as parameter.
   Initializes winner board and main play board
  */
  MainBoard(unsigned int boardSize);
  /*  Function: addWinnerOfInnerBoard
Places figure on the winner board.
Parameters:
coordinates - Point (x,y) where figure should be placed.
figure - figure of the winner of the inner board.
          */
  void addWinnerOfInnerBoard(Point &coordinates, char &figure);
  /*  Function: makeMove
Places figure on the one of the inner boards of the main board.
Parameters:
boardCoordinates - Point (x,y) indicating which inner board should be modified.
innerCoordinates - Point (x,y) of the inner board which should be filled
   with the figure.
figure - figure to be placed.
      */
  void makeMove(Point &boardCoordinates, Point &innerCoordinates, char figure);
  /*  Function: toJson
    Converts main board to json format which is used in communication with the
  client. Parameters:

  isNested - boolean value indicating if json is nested inside other json,
      because it has impact on structure of json
              */
  std::string toJson(bool isNested) override;
  /*  Function: winnerBoardToJson
    Converts winner board to json format which is used in communication with the
  client. Parameters:

  isNested - boolean value indicating if json is nested inside other json,
      because it has impact on structure of json
              */
  std::string winnerBoardToJson(bool isNested);
  /*  Function: getInnerBoard
    Getter of inner board

  point - coordinates of inner board in main board
              */
  const InnerBoard &getInnerBoard(Point point) const;
  /*  Function: getWinnerBoardCell
    Getter of figure inside given cell in winner board

    point - coordinates of cell of winner board

              */
  char getWinnerBoardCell(Point point);
  const InnerBoard &getWinnerBoard() const;
};

#endif // ULTIMATETICTACTOESERVER_MAINBOARD_HPP
