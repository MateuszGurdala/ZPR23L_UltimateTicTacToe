
#include "../../include/entities/Player.hpp"

std::string Player::GetName() const { return name; }

char Player::GetSymbol() const { return symbol; }

Player::Player(char symbol) : symbol(symbol) {}
