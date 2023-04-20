#include "../../include/gameengine/GameHandler.hpp"

GameHandler::GameHandler(std::unique_ptr <HumanPlayer> hostPlayer, std::unique_ptr <Player> secondPlayer,
                         std::unique_ptr <GameEngine> gameEngine)
                         : hostPlayer(std::move(hostPlayer)), secondPlayer(std::move(secondPlayer)),
                         gameEngine(std::move(gameEngine)) {}

void GameHandler::StartGame() {

}

bool GameHandler::CheckIfGameEnd() {
    return false;
}

void GameHandler::PerformTurn() {

}
