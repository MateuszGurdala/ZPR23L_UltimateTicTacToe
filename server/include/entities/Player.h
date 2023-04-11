
#ifndef ULTIMATETICTACTOESERVER_PLAYER_H
#define ULTIMATETICTACTOESERVER_PLAYER_H

#include <string>

class Player {
private:
    std::string _symbol; //TODO to enum
    std::string _name;
    int _points = 0;
public:
    Player();
};

#endif //ULTIMATETICTACTOESERVER_PLAYER_H
