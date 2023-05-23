#include "../include/gameengine/GameHandler.hpp"
#include <memory>
#include <iostream>

//TODO  testing purposes only - delete later
int main() {
//    std::cout << "INNERBOARD JSON TEST" << std::endl;
//    auto board = std::make_unique<InnerBoard>(3);
//    Point innerBoardCoords1 = Point(0,0);
//    Point innerBoardCoords2 = Point(1,1);
//    char x = 'X';
//    char o = 'O';
//    board->PlaceFigure(innerBoardCoords1, x);
//    board->PlaceFigure(innerBoardCoords2, o);
//    std::cout << board->ToJson(false) << std::endl;
//    std::cout << "------------------------------------" << std::endl;
//    auto mainBoard = std::make_unique<MainBoard>(3);
//    auto json = mainBoard->ToJson(false);
//    auto winnerBoardJson = mainBoard->WinnerBoardToJson(false);
//    std::cout << "WINNER BOARD JSON TEST" << std::endl;
//    std::cout << winnerBoardJson << std::endl;
//    std::cout << "------------------------------------" << std::endl;
//    auto gameEngine = std::make_unique<GameEngine>(std::move(mainBoard));
//    std::array<Point, 2> arr = {Point(1, 2), Point(0, 1)};
//    std::cout << "GAME STATE JSON TEST" << std::endl;
//    auto handler = std::make_unique<GameHandler>(3, "Krystian", 'X', false, "Mateusz");
//    auto stateJson = handler->GameStateAsJson();
//    std::cout << stateJson << std::endl;
//    auto jsonMove = handler->MoveAsJson(false, arr, true);
//    std::cout << "MOVE RESPONSE JSON TEST" << std::endl;
//    std::cout <<  jsonMove << std::endl;
//    std::cout << "------------------------------------" << std::endl;
//    std::cout << "GAME ENDED JSON TEST" << std::endl;
//    auto winnerJson = handler->EndGameAsJson(false);
//    std::cout << winnerJson << std::endl;
//    std::cout << "GAME CREATED JSON TEST" << std::endl;
//    auto createJson = handler ->CreateGameAsJson(true);
//    std::cout << createJson << std::endl;


    //CLIENT PROVIDE PROPERTIES TO HANDLER
    auto handler = std::make_unique<GameHandler>(3, "Krystian", 'X', false, "Mati");
    //GAME CREATED -  handler ->CreateGameAsJson(true); IF FAIL handler ->CreateGameAsJson(false);
    while(handler->GetCurrentGameState() != "Finished")
    {
        // SEND GAME STATE - handler->GameStateAsJson();
        // SEND GAME BOARD - handler->BoardStateAsJson();
        // CHOOSE COORDINATES (PLAYER/COMPUTER) handler->ChooseCoordinatesOfMove();
        // CHOOSE SEGMENT PickSegmentAsJson(false, Point &segment, bool isValid);
        handler->GameStateAsJson();
        handler->BoardStateAsJson();
        unsigned int outer_x;
        unsigned int outer_y;
        unsigned int inner_x;
        unsigned int inner_y;
        std::cout << "Enter x and y coordinates for outerBoard: " << std::endl;
        std::cin >> outer_x;
        std::cin >> outer_y;
        std::cout << "Enter x and y coordinates for innerBoard: " << std::endl;
        std::cin >> inner_x;
        std::cin >> inner_y;
        Point oPoint = Point(outer_x,outer_y);
        Point iPoint = Point(inner_x, inner_y);
        if(handler->PerformMoveValidation(oPoint, iPoint))
        {
            handler->PerformTurn(oPoint, iPoint);
        }
        else
        {
            std::cout << "INVALID MOVE" << std::endl;
        }
    }
    std::cout << "GAME FINISHED" << std::endl;

}