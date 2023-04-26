#ifndef ULTIMATETICTACTOESERVER_GAMEENGINE_H
#define ULTIMATETICTACTOESERVER_GAMEENGINE_H

#include "../entities/MainBoard.hpp"

class GameEngine {
private:
    std::unique_ptr<MainBoard> mainBoard;
    std::vector<Point> availableOuterBoardMoves;
    std::vector<Point> availableInnerBoardMoves;
public:
    GameEngine(std::unique_ptr<MainBoard> mainBoard);

    bool CheckLocalWinner();
    bool CheckGlobalWinner();
    void HandleMove(Point& boardCoordinates, Point& innerCoordinates, char figure);
    void Print();
};

#endif //ULTIMATETICTACTOESERVER_GAMEENGINE_H
