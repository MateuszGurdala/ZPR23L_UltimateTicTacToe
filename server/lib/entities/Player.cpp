
#include "../../include/entities/Player.hpp"

std::string Player::getName() const { return name; }

char Player::getSymbol() const { return symbol; }

Player::Player(char symbol) : symbol(symbol) {}
