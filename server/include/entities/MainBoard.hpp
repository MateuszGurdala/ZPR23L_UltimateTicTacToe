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
    void MakeMove(Point boardCoordinates, Point innerCoordinates, char figure);
    auto GetInnerBoardVerticalValues(Point playBoardCoordinates, Point innerBoardRowAndColumn);
    auto GetInnerBoarHorizontalValues(Point playBoardCoordinates, Point innerBoardRowAndColumn);
    auto GetInnerBoardLeftDiagonalValues(Point playBoardCoordinates, Point innerBoardRowAndColumn);
    auto GetInnerBoardRightDiagonalValues(Point playBoardCoordinates, Point innerBoardRowAndColumn);
};

#endif //ULTIMATETICTACTOESERVER_MAINBOARD_HPP
