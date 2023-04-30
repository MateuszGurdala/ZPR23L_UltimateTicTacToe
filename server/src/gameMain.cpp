#include "../include/gameengine/GameHandler.hpp"
#include <memory>
#include <iostream>

//TODO  testing purposes only - delete later
int main() {
/*    auto handler = std::make_unique<GameHandler>();
    auto coords = handler->ChooseCoordinatesOfMove();
    handler->PerformTurn(coords[0], coords[1]);
    handler->Print();*/


    std::cout << "INNERBOARD JSON TEST" << std::endl;
    auto board = std::make_unique<InnerBoard>(3);
    Point innerBoardCoords1 = Point(0,0);
    Point innerBoardCoords2 = Point(1,1);
    char x = 'X';
    char o = 'O';
    board->PlaceFigure(innerBoardCoords1, x);
    board->PlaceFigure(innerBoardCoords2, o);
    std::cout << board->ToJson(false) << std::endl;
    std::cout << "------------------------------------" << std::endl;
    auto mainBoard = std::make_unique<MainBoard>(3);
    auto json = mainBoard->ToJson(false); // CAN BE SEEN IN CLIENT SINCE ITS TOO LARGE TO DEMONSTRATE IN TERMINAL
    auto winnerBoardJson = mainBoard->WinnerBoardToJson(false);
    std::cout << "WINNER BOARD JSON TEST" << std::endl;
    std::cout << winnerBoardJson << std::endl;
    std::cout << "------------------------------------" << std::endl;
    auto gameEngine = std::make_unique<GameEngine>(std::move(mainBoard));
    std::array<Point, 2> arr = {Point(1, 2), Point(0, 1)};
    auto jsonMove = gameEngine->MoveAsJson(false, arr, true);
    std::cout << "MOVE RESPONSE JSON TEST" << std::endl;
    std::cout <<  jsonMove << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "GAME STATE JSON TEST" << std::endl;
    auto handler = std::make_unique<GameHandler>();
    auto stateJson = handler->GameStateAsJson();
    std::cout << stateJson << std::endl;
}