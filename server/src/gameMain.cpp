#include "../include/gameengine/GameHandler.hpp"
#include <memory>

int main() {
    auto handler = std::make_unique<GameHandler>();
    handler->PerformTurn(Point(1,1), Point(1,1));
    handler->PerformTurn(Point(0,0), Point(0,0));
    handler->PerformTurn(Point(0,0), Point(1,1));
    handler->Print();
}