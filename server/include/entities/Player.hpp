
#ifndef ULTIMATETICTACTOESERVER_PLAYER_HPP
#define ULTIMATETICTACTOESERVER_PLAYER_HPP

#include <string>

class Player {
protected:
    char symbol;
    int points = 0;
public:
    Player(char symbol);
    int GetPoints() const;
    void IncrementPoints();
};

#endif //ULTIMATETICTACTOESERVER_PLAYER_HPP
