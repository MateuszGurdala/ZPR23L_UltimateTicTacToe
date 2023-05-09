
#include <utility>

#include "../../include/entities/HumanPlayer.hpp"

HumanPlayer::HumanPlayer(char symbol,std::string name): Player(symbol){
    //TODO only letters
    if(name.length() >= 20)
    {
        throw std::invalid_argument("name should have 20 characters or less");
    }
    this->name = std::move(name);
}


//TODO
std::array<Point, 2> HumanPlayer::ChooseMove([[maybe_unused]]const std::vector<Point> &availableOuterBoardMoves,
                                             [[maybe_unused]]std::vector<std::vector<Point>> availableInnerBoardMoves, [[maybe_unused]]unsigned int boardSize) {
    return std::array<Point, 2>();
}
