

#ifndef ULTIMATETICTACTOESERVER_COMPUTERPLAYER_HPP
#define ULTIMATETICTACTOESERVER_COMPUTERPLAYER_HPP

#include <array>
#include "Player.hpp"
#include "BoardBase.hpp"
#include <vector>
#include <random>

class ComputerPlayer : public Player {
private:
    Point& SimulateMove(const std::vector<Point>& availableMoves);
public:
    std::array<Point, 2> ChooseMove(const std::vector<Point>& availableOuterBoardMoves,
                                    std::vector<std::vector<Point>> availableInnerBoardMoves, int boardSize) override;

    ComputerPlayer(char symbol);
};

#endif //ULTIMATETICTACTOESERVER_COMPUTERPLAYER_HPP
