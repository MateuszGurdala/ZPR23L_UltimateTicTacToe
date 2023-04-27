#ifndef ULTIMATETICTACTOESERVER_GAMEENGINE_H
#define ULTIMATETICTACTOESERVER_GAMEENGINE_H

#include "../entities/MainBoard.hpp"

class GameEngine {
private:
    std::unique_ptr<MainBoard> mainBoard;
    std::vector<Point> availableOuterBoardMoves;
    std::vector<std::vector<Point>> availableInnerBoardMoves;
    static std::vector<Point> InitializeAvailableSingleBoardMoves(int boardSize);
    static std::vector<std::vector<Point>> InitializeAvailableInnerBoardMoves(int boardSize);
public:
    GameEngine(std::unique_ptr<MainBoard> mainBoard);
    int GetBoardSize();
    std::vector<Point>& getAvailableOuterBoardMoves();
    std::vector<std::vector<Point>>& getAvailableInnerBoardMoves();
    bool CheckLocalWinner();
    bool CheckGlobalWinner();
    void HandleMove(Point& boardCoordinates, Point& innerCoordinates, char figure);
    void Print();
};

#endif //ULTIMATETICTACTOESERVER_GAMEENGINE_H
