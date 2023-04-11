#ifndef ULTIMATETICTACTOESERVER_MAINBOARD_H
#define ULTIMATETICTACTOESERVER_MAINBOARD_H

#include "InnerBoard.h"
#include <vector>

class MainBoard {
private:
    std::vector<InnerBoard> _gameBoard;
    const int _size = _gameBoard[0].GetBoardSize();
public:
    MainBoard();
};

#endif //ULTIMATETICTACTOESERVER_MAINBOARD_H
