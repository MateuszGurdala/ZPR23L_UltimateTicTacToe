#ifndef ULTIMATETICTACTOESERVER_GAMEENGINE_H
#define ULTIMATETICTACTOESERVER_GAMEENGINE_H

#include "../entities/MainBoard.hpp"

/*  Class: GameEngine
    Class responsible for checking and handling logic of the game. It includes MainBoard,
    lists all available moves, checks if game has the winner. Keeps the value
    of current played segment. Checks and sets valid game moves for whole game
    and for current turn.
 */
class GameEngine {
private:
    std::unique_ptr<MainBoard> mainBoard;
    int currentSegment;
    std::vector<std::vector<Point>> allAvailableBoardMoves;
    std::vector<std::vector<Point>> currentLegalMoves;
    std::vector<Point> initializeAvailableSingleBoardMoves();
    std::vector<std::vector<Point>> initializeAvailableInnerBoardMoves();
    static bool areAllValuesTheSame(const std::vector<char>& values);

public:
    GameEngine(std::unique_ptr<MainBoard> mainBoard);
    unsigned int GetBoardSize();
    std::vector<std::vector<Point>>& GetAvailableInnerBoardMoves();
    bool CheckForLocalWinner(Point& mainBoardCoordinates, Point& innerBoardCellCoordinates, char figure);
    bool CheckForGlobalWinner(Point& changedWinnerBoardCellCoordinates);
    void HandleMove(Point& boardCoordinates, Point& innerCoordinates, char figure);
    std::string GetWinnerBoardAsJson(bool isNested);
    std::string GetBoardAsJson(bool isNested);

    void RemovePointFromAllAvailableMoves(unsigned int innerBoardIndex, Point &pointOfInnerBoardToRemove);

    void UpdateCurrentLegalMoves(Point &innerBoardCoordinates);
    bool IsSegmentChoosen(Point &innerBoardCoordinates);
    std::array<Point, 2> HandleComputerMove();
    int GetCurrentSegment();
    bool CheckIfAnyMovesLeft();
};

#endif //ULTIMATETICTACTOESERVER_GAMEENGINE_H
