#include "../include/gameengine/GameHandler.hpp"
#include <memory>
#include <iostream>

int main() {
/*    auto handler = std::make_unique<GameHandler>();
    auto coords = handler->ChooseCoordinatesOfMove();
    handler->PerformTurn(coords[0], coords[1]);
    handler->Print();*/
    auto board = std::make_unique<InnerBoard>(3);
    std::cout << board->ToJson(false) << std::endl;
}