#ifndef ULTIMATETICTACTOESERVER_GAMEHANDLER_H
#define ULTIMATETICTACTOESERVER_GAMEHANDLER_H

#include "../entities/HumanPlayer.hpp"
#include "../entities/Player.hpp"
#include "GameEngine.hpp"
#include <memory>

class GameHandler {
private:

    std::unique_ptr<HumanPlayer> hostPlayer;
    std::unique_ptr<Player> secondPlayer;
    std::unique_ptr<GameEngine> gameEngine;
    bool isHostTurn;
    void startGame();
public:
    bool CheckIfGameEnd();
    void PerformTurn(Point boardCoordinates, Point innerCoordinates);
    GameHandler(std::unique_ptr<HumanPlayer> hostPlayer, std::unique_ptr<Player> secondPlayer, std::unique_ptr<GameEngine> gameEngine);
    GameHandler();

    void Print();
};

#endif //ULTIMATETICTACTOESERVER_GAMEHANDLER_H
