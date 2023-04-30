#ifndef ULTIMATETICTACTOESERVER_GAMEHANDLER_H
#define ULTIMATETICTACTOESERVER_GAMEHANDLER_H

#include "../entities/HumanPlayer.hpp"
#include "../entities/Player.hpp"
#include "GameEngine.hpp"
#include <memory>

/*  Class: GameHandler
    Wrapper class for game logic which also links players with the game. It holds the logic of performing turn and invokes
    methods of gameEngine. It also holds the game state.
    See also:
    <GameEngine>
 */
class GameHandler {
private:

    std::unique_ptr<HumanPlayer> hostPlayer;
    std::unique_ptr<Player> secondPlayer;
    std::unique_ptr<GameEngine> gameEngine;
    bool isHostTurn = false;
    void startGame();
public:
    bool CheckIfGameEnd();
    void PerformTurn(Point boardCoordinates, Point innerCoordinates);
    GameHandler(std::unique_ptr<HumanPlayer> hostPlayer, std::unique_ptr<Player> secondPlayer, std::unique_ptr<GameEngine> gameEngine);
    GameHandler();
    std::array<Point, 2> ChooseCoordinatesOfMove();
    std::string GameStateAsJson();
    void Print();
};

#endif //ULTIMATETICTACTOESERVER_GAMEHANDLER_H
