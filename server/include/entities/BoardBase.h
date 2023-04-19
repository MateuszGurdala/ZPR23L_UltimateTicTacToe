#ifndef ULTIMATETICTACTOESERVER_BOARDBASE_H
#define ULTIMATETICTACTOESERVER_BOARDBASE_H

class BoardBase {
protected:
    int boardSize;
    virtual void FillBoard() = 0;
public:
    BoardBase(int boardSize);
    virtual ~BoardBase() = default;
    int GetBoardSize() const;
};

#endif //ULTIMATETICTACTOESERVER_BOARDBASE_H
