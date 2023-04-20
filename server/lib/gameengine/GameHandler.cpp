#include "../../include/gameengine/GameHandler.hpp"

GameHandler::GameHandler(std::unique_ptr <HumanPlayer> hostPlayer, std::unique_ptr <Player> secondPlayer,
                         std::unique_ptr <GameEngine> gameEngine)
                         : hostPlayer(std::move(hostPlayer)), secondPlayer(std::move(secondPlayer)),
                         gameEngine(std::move(gameEngine)) {}

GameHandler::GameHandler()
{
    startGame();
}

void GameHandler::startGame() {
    hostPlayer = std::make_unique<HumanPlayer>('X', std::string("testHost"));
    secondPlayer = std::make_unique<HumanPlayer>('O', std::string("testGuest"));

    auto mainBoard = std::make_unique<MainBoard>(3);
    gameEngine = std::make_unique<GameEngine>(std::move(mainBoard));
}

bool GameHandler::CheckIfGameEnd() {
    return false;
}
void GameHandler::Print() {
    gameEngine->Print();
}

void GameHandler::PerformTurn(Point boardCoordinates, Point innerCoordinates) {

    char currentFigure;
    if(isHostTurn)
    {
        currentFigure = hostPlayer->GetSymbol();
    }
    else
    {
        currentFigure = secondPlayer->GetSymbol();
    }
    gameEngine->HandleMove(boardCoordinates, innerCoordinates, currentFigure);
    isHostTurn = !isHostTurn;
}
