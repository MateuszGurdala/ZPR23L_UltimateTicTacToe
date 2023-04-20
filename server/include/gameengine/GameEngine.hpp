#ifndef ULTIMATETICTACTOESERVER_GAMEENGINE_H
#define ULTIMATETICTACTOESERVER_GAMEENGINE_H

#include "../entities/MainBoard.hpp"

class GameEngine {
private:
    MainBoard mainBoard;
public:
    bool CheckWinner();
    GameEngine();
};

#endif //ULTIMATETICTACTOESERVER_GAMEENGINE_H
