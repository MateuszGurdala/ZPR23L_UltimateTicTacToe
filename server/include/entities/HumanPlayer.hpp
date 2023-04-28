#ifndef ULTIMATETICTACTOESERVER_HUMANPLAYER_HPP
#define ULTIMATETICTACTOESERVER_HUMANPLAYER_HPP

#include "Player.hpp"

class HumanPlayer : public Player {
private:
public:
    HumanPlayer(char symbol,std::string name);
    std::array<Point, 2> ChooseMove(const std::vector<Point>& availableOuterBoardMoves,
                                    std::vector<std::vector<Point>> availableInnerBoardMoves, int boardSize) override;
};

#endif //ULTIMATETICTACTOESERVER_HUMANPLAYER_HPP
