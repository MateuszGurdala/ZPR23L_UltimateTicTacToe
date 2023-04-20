
#include <memory>
#include "../../include/gameengine/GameEngine.hpp"

GameEngine::GameEngine(std::unique_ptr <MainBoard> mainBoard) : mainBoard(std::move(mainBoard)) {}

void GameEngine::HandleMove(Point& boardCoordinates, Point& innerCoordinates, char figure) {
    mainBoard->MakeMove(boardCoordinates,innerCoordinates,figure);
}

void GameEngine::Print()
{
    mainBoard->Print();
}
