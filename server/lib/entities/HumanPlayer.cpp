
#include <utility>

#include "../../include/entities/HumanPlayer.hpp"

HumanPlayer::HumanPlayer(char symbol,std::string name): Player(symbol), name(std::move(name)) {}

