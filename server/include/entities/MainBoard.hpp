#ifndef ULTIMATETICTACTOESERVER_MAINBOARD_HPP
#define ULTIMATETICTACTOESERVER_MAINBOARD_HPP

#include "InnerBoard.hpp"
#include <vector>

class MainBoard : public BoardBase {
private:
    std::vector<std::vector<std::unique_ptr<InnerBoard>>> mainPlayBoard;
    std::unique_ptr<std::unique_ptr<char[]>[]> winnerBoard;
    void FillBoard() override;
public:
    MainBoard(int boardSize);
    void Print() const;
    void AddWinnerOfInnerBoard(Point coordinates, char figure);
};

#endif //ULTIMATETICTACTOESERVER_MAINBOARD_HPP