#ifndef ULTIMATETICTACTOESERVER_GAMEENGINE_H
#define ULTIMATETICTACTOESERVER_GAMEENGINE_H

#include "../entities/MainBoard.hpp"

class GameEngine {
private:
    std::unique_ptr<MainBoard> mainBoard;
public:
    bool CheckLocalWinner();
    bool CheckGlobalWinner();
    void HandleMove(Point boardCoordinates, Point innerCoordinates, char figure);
    GameEngine(std::unique_ptr<MainBoard> mainBoard);
};

#endif //ULTIMATETICTACTOESERVER_GAMEENGINE_H
