#ifndef ULTIMATETICTACTOESERVER_BOARDBASE_HPP
#define ULTIMATETICTACTOESERVER_BOARDBASE_HPP

#include <memory>
#include <stdexcept>

/*  Struct: Point
    Contains coordinates of board defined as (x,y) which in terms
    of board translates to (index of row, index of column)
*/
struct Point {
  unsigned int x;
  unsigned int y;
  Point(unsigned int x_, unsigned int y_) : x(x_), y(y_) {}
  Point() : x(0), y(0) {}
};

/*  Class: BoardBase
        Base class for in game boards. Contains virtual
        methods used in all types of Boards and
        stores information about size of the board.

    See Also:
      <InnerBoard>, <MainBoard>
 */
class BoardBase {
protected:
  unsigned int boardSize;
  virtual void FillBoard() = 0;

public:
  /*  Constructor: BoardBase

    Base constructor which only takes boardSize. Derived by other
    Board classes
    See Also:

   <InnerBoard>, <OuterBoard>
        */
  BoardBase(unsigned int boardSize);
  virtual ~BoardBase() = default;

  unsigned int GetBoardSize() const;
  /*  Function: VerifyCoordinates
  checks if coordinates of point are valid in terms of placing it on the board
   (being inside the bounds)

  Parameters:
      point - (x,y) coordinates of the board
          See also:
      <Point>
          */
  void VerifyCoordinates(Point point) const;
  /*  Function: VerifyFigure
  checks if figure is allowed to be placed in the board. Currently,
   we accept only 'X' and 'O' as valid figures.

  Parameters:
      figure - figure to be placed inside the board
          */
  static void VerifyFigure(char figure);
  virtual std::string ToJson(bool isNested) = 0;
};

#endif // ULTIMATETICTACTOESERVER_BOARDBASE_HPP
