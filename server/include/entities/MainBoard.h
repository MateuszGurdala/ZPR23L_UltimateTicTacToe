#ifndef ULTIMATETICTACTOESERVER_MAINBOARD_H
#define ULTIMATETICTACTOESERVER_MAINBOARD_H

#include "InnerBoard.h"
#include <vector>

class MainBoard : public BoardBase {
private:
    std::vector<std::vector<std::unique_ptr<InnerBoard>>> mainPlayBoard;
    void FillBoard() override;
public:
    MainBoard(int boardSize);
    void Print() const;

};

#endif //ULTIMATETICTACTOESERVER_MAINBOARD_H
