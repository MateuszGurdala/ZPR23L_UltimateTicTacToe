
#include "../../include/entities/Player.hpp"

void Player::IncrementPoints() {
    points++;
}

int Player::GetPoints() const {
    return points;
}

char Player::GetSymbol() const {
    return symbol;
}

Player::Player(char symbol) : symbol(symbol){}
