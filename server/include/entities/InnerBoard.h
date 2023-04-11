#ifndef ULTIMATETICTACTOESERVER_INNERBOARD_H
#define ULTIMATETICTACTOESERVER_INNERBOARD_H

#include <vector>
#include <array>

class InnerBoard {
private:
    static int _arraySize;
    std::array<std::array<char, _arraySize>, _arraySize> playBoardArray = {{' '}};
public:
    InnerBoard();
    int GetBoardSize();
};

#endif //ULTIMATETICTACTOESERVER_INNERBOARD_H
