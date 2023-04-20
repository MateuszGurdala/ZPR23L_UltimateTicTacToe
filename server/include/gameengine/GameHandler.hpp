#ifndef ULTIMATETICTACTOESERVER_GAMEHANDLER_H
#define ULTIMATETICTACTOESERVER_GAMEHANDLER_H

#include "../entities/HumanPlayer.hpp"
#include "../entities/Player.hpp"
#include "GameEngine.hpp"

class GameHandler {
private:
    HumanPlayer hostPlayer;
    Player secondPlayer;
    GameEngine gameEngine;
public:
    void StartGame();
    bool IsPlayerWinner();
    GameHandler();
};

#endif //ULTIMATETICTACTOESERVER_GAMEHANDLER_H
