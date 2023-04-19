
#include "../../include/entities/Player.h"

void Player::IncrementPoints() {
    points++;
}

int Player::GetPoints() const {
    return points;
}

Player::Player(char symbol) : symbol(symbol) {}
