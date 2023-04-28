#include "../include/gameengine/GameHandler.hpp"
#include <memory>
#include <iostream>

int main() {
/*    auto handler = std::make_unique<GameHandler>();
    auto coords = handler->ChooseCoordinatesOfMove();
    handler->PerformTurn(coords[0], coords[1]);
    handler->Print();*/

// INNERBOARD JSON TEST
/*    auto board = std::make_unique<InnerBoard>(3);
    std::cout << board->ToJson(false) << std::endl;*/

// MAINBOARD JSON TEST
    auto mainBoard = std::make_unique<MainBoard>(3);
    auto json = mainBoard->ToJson(false);
    auto gameEngine = std::make_unique<GameEngine>(std::move(mainBoard));
    std::array<Point, 2> arr = {Point(1, 2), Point(0, 1)};
    auto jsonMove = gameEngine->MoveAsJson(false, arr, true);
    std::cout <<  jsonMove << std::endl;
}