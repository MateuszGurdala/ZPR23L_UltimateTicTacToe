#ifndef ULTIMATETICTACTOESERVER_BOARDBASE_HPP
#define ULTIMATETICTACTOESERVER_BOARDBASE_HPP

#include <stdexcept>

struct Point {
    int x;
    int y;
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
};


#endif //ULTIMATETICTACTOESERVER_BOARDBASE_HPP
