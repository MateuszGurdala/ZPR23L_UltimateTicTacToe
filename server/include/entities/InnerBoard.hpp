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
    void MakeMove(Point coordinates, char figure);
};

#endif //ULTIMATETICTACTOESERVER_INNERBOARD_HPP