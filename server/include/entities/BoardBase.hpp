#ifndef ULTIMATETICTACTOESERVER_BOARDBASE_HPP
#define ULTIMATETICTACTOESERVER_BOARDBASE_HPP

#include <stdexcept>

struct Point {
    int x;
    int y;
    Point(int x_, int y_) : x(x_), y(y_) {}
    Point() : x(0), y(0) {}
};

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
