#ifndef ULTIMATETICTACTOESERVER_BOARDBASE_HPP
#define ULTIMATETICTACTOESERVER_BOARDBASE_HPP

#include <stdexcept>

/*  Struct: Point
    Contains coordinates of board defined as (x,y) which translates to (index of row, index of column)
*/
struct Point {
    int x;
    int y;
    Point(int x_, int y_) : x(x_), y(y_) {}
    Point() : x(0), y(0) {}
};

/*  Class: BoardBase
        Base class for in game boards. Contains virtual methods used in all types of Boards and
        stores information about size of the board.

    See Also:
      <InnerBoard>, <MainBoard>
 */
class BoardBase {
protected:
    int boardSize;
    virtual void FillBoard() = 0;
public:
    BoardBase(int boardSize);
    virtual ~BoardBase() = default;
    int GetBoardSize() const;
    void VerifyCoordinates(Point point) const;
    static void VerifyFigure(char figure) ;
    virtual std::string ToJson(bool isNested) = 0;
};


#endif //ULTIMATETICTACTOESERVER_BOARDBASE_HPP
