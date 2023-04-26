

#ifndef ULTIMATETICTACTOESERVER_COMPUTERPLAYER_HPP
#define ULTIMATETICTACTOESERVER_COMPUTERPLAYER_HPP

#include <array>
#include "Player.hpp"
#include "BoardBase.hpp"
#include <vector>
#include <random>

class ComputerPlayer : public Player {
private:
    ComputerPlayer(char symbol);
    Point& SimulateMove(const std::vector<Point>& availableMoves);
public:
    std::array<Point, 2> ChooseMove(const std::vector<Point>& availableOuterBoardMoves,
                                                    const std::vector<Point>& availableInnerBoardMoves ) override;
};

#endif //ULTIMATETICTACTOESERVER_COMPUTERPLAYER_HPP
