#ifndef ULTIMATETICTACTOESERVER_INNERBOARD_HPP
#define ULTIMATETICTACTOESERVER_INNERBOARD_HPP

#include <vector>
#include <array>
#include <memory>
#include "BoardBase.hpp"

class InnerBoard : public BoardBase{
private:
    std::unique_ptr<std::unique_ptr<char[]>[]> playBoard;
    void FillBoard() override;

public:
    InnerBoard(int boardSize);
    std::string ToString() const;
    auto GetLeftDiagonalValues(Point& playBoardCoordinates, Point& innerBoardRowAndColumn);
    auto GetRightDiagonalValues(Point& playBoardCoordinates, Point& innerBoardRowAndColumn);
    auto GetHorizontalValues(Point& playBoardCoordinates, Point& innerBoardRowAndColumn);
    auto GetVerticalValues(Point& playBoardCoordinates, Point& innerBoardRowAndColumn);
    std::string ToJson(bool isNested) override;
    void PlaceFigure(Point& coordinates, char &figure);
};

#endif //ULTIMATETICTACTOESERVER_INNERBOARD_HPP
