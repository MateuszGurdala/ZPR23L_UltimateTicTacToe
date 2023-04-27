#include "../include/gameengine/GameHandler.hpp"
#include <memory>

int main() {
    auto handler = std::make_unique<GameHandler>();
    auto coords = handler->ChooseCoordinatesOfMove();
    handler->PerformTurn(coords[0], coords[1]);
    handler->Print();
}