#ifndef ULTIMATETICTACTOESERVER_HUMANPLAYER_HPP
#define ULTIMATETICTACTOESERVER_HUMANPLAYER_HPP

#include "Player.hpp"

class HumanPlayer : public Player {
private:
    std::string name;
public:
    HumanPlayer(char symbol,std::string name);
};

#endif //ULTIMATETICTACTOESERVER_HUMANPLAYER_HPP
