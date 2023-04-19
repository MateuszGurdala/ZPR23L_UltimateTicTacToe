#ifndef ULTIMATETICTACTOESERVER_HUMANPLAYER_H
#define ULTIMATETICTACTOESERVER_HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player {
private:
    std::string name;
public:
    HumanPlayer(char symbol,std::string &name);
};

#endif //ULTIMATETICTACTOESERVER_HUMANPLAYER_H
