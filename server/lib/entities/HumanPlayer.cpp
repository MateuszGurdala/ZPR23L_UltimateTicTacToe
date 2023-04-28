
#include <utility>

#include "../../include/entities/HumanPlayer.hpp"

HumanPlayer::HumanPlayer(char symbol,std::string name): Player(symbol){
    this->name = name;
}


//TODO
std::array<Point, 2> HumanPlayer::ChooseMove([[maybe_unused]]const std::vector<Point> &availableOuterBoardMoves,
                                             [[maybe_unused]]std::vector<std::vector<Point>> availableInnerBoardMoves, [[maybe_unused]]int boardSize) {
    return std::array<Point, 2>();
}
