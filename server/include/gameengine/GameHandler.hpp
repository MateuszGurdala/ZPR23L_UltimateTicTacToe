#ifndef ULTIMATETICTACTOESERVER_GAMEHANDLER_H
#define ULTIMATETICTACTOESERVER_GAMEHANDLER_H

#include "../entities/HumanPlayer.hpp"
#include "../entities/Player.hpp"
#include "GameEngine.hpp"
#include "GameStage.hpp"
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
    bool isSecondPlayerComputer;
    std::unique_ptr<GameStage> currentGameState;
    void startGame(unsigned int boardSize, const std::string& hostName, char hostSymbol, bool isPlayerVsComputer = true, const std::string& guestName = "");
    void handleGameEnd();
public:
    const GameStage& GetGameStage();
    bool PerformMoveValidation(Point boardCoordinates, Point innerCoordinates);
    void PerformTurn(Point boardCoordinates, Point innerCoordinates);
    GameHandler(std::unique_ptr<HumanPlayer> hostPlayer, std::unique_ptr<Player> secondPlayer, std::unique_ptr<GameEngine> gameEngine);
    GameHandler(unsigned int boardSize,
                char hostSymbol, bool isPlayerVsComputer, const std::string &hostName = "Host",
                const std::string &guestName = "Guest");
    std::string GameStateAsJson();
    std::string EndGameAsJson(bool isPlayerSurrender);
    std::string CreateGameAsJson(bool isSuccess);
    std::string MoveAsJson(bool isNested, std::array<Point, 2> move, bool isValid);
    std::string PickSegmentAsJson(bool isNested, Point &segment, bool isValid);
    std::string WinnerBoardAsJson();
    std::string BoardStateAsJson();
};

#endif //ULTIMATETICTACTOESERVER_GAMEHANDLER_H
