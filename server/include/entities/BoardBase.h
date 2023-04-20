#ifndef ULTIMATETICTACTOESERVER_BOARDBASE_H
#define ULTIMATETICTACTOESERVER_BOARDBASE_H

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


#endif //ULTIMATETICTACTOESERVER_BOARDBASE_H
