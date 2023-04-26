
#include <memory>
#include "../../include/gameengine/GameEngine.hpp"

GameEngine::GameEngine(std::unique_ptr <MainBoard> mainBoard) : mainBoard(std::move(mainBoard)) {
    availableOuterBoardMoves =
    availableInnerBoardMoves =
}



void GameEngine::HandleMove(Point& boardCoordinates, Point& innerCoordinates, char figure) {
    mainBoard->MakeMove(boardCoordinates,innerCoordinates,figure);
}

void GameEngine::Print()
{
    mainBoard->Print();
}

//TODO implement
bool GameEngine::CheckLocalWinner() {
    return false;
}

//TODO implement
bool GameEngine::CheckGlobalWinner() {
    return false;
}
