
#include "../../include/entities/Player.hpp"

void Player::IncrementPoints() {
    points++;
}

int Player::GetPoints() const {
    return points;
}

Player::Player(char symbol) : symbol(symbol) {}
