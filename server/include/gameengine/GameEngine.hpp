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
      /*  Constructor: GameEngine
    Initializes engine of the game. Creates mainBoard since it is the core of
       the game. Marks all moves on board as legal by calling helper methods.
    */
    GameEngine(std::unique_ptr<MainBoard> mainBoard);
    /*  Function: GetBoardSize
        Returns size of the board that is a part of the current game
    */
    unsigned int GetBoardSize();
    /*  Function: GetAvailableInnerBoardMoves
          Returns remaining moves in the game.
    */
    std::vector<std::vector<Point>>& GetAvailableInnerBoardMoves();
    /*  Function: CheckForLocalWinner
        Check if there is a winner in the inner board after the move.
        Parameters:
        mainBoardCoordinates - coordinates of inner board where we check
        for the winner
        innerBoardCellCoordinates - cell of the inner board that was changed
     */
    bool CheckForLocalWinner(Point& mainBoardCoordinates, Point& innerBoardCellCoordinates, char figure);
    /*  Function: CheckForGlobalWinner
        Check if there is a winner of the whole game when there is a change in
        the winner board
          Parameters:
          changedWinnerBoardCellCoordinates - cell that was changed in the
          winner board
    */
    bool CheckForGlobalWinner(Point& changedWinnerBoardCellCoordinates);
    /*  Function: HandleMove
    Makes move on the main board and calls method that
     removes it from legal moves.
    */
    void HandleMove(Point& boardCoordinates, Point& innerCoordinates, char figure);
    /*  Function: GetWinnerBoardAsJson
  Converts winner board to json format which is used in communication with the client.
     This function just passes method from the MainBoard. Further used in game handler.
  Parameters:

    isNested - boolean value indicating if json is nested inside other json,
        because it has impact on structure of json
                */
    std::string GetWinnerBoardAsJson(bool isNested);
    /*  Function: GetBoardAsJson
  Converts main board to json format which is used in communication with the client.
     This function just passes method from the MainBoard. Further used in game handler.
  Parameters:

    isNested - boolean value indicating if json is nested inside other json,
        because it has impact on structure of json
                */
    std::string GetBoardAsJson(bool isNested);

    /*  Function: RemovePointFromAllAvailableMoves
Removes point from the all available moves 2d vector.
     Parameters:
      innerBoardIndex - index of segment where the move became invalid
      innerCoordinates - Point (x,y) chosen cell inside inner board which
                      became filled
*/
    void RemovePointFromAllAvailableMoves(unsigned int innerBoardIndex, Point &pointOfInnerBoardToRemove);
    /*  Function: UpdateCurrentLegalMoves
     Updates legal moves which will be available in the next turn based on the
     previously chosen cell, then the segment index is determined
*/
    void UpdateCurrentLegalMoves(Point &innerBoardCoordinates);
        /*  Function: IsSegmentChoosen
         Determines if segment (coordinates of outer board) are chosen by game logic.
         If not currentSegment should be set to -1. This is the value interpreted
         by the client.
    */
    bool IsSegmentChoosen(Point &innerBoardCoordinates);
    /*  Function: HandleComputerMove
      Invokes simulation of the move for computer player
    */
    std::array<Point, 2> HandleComputerMove();
    /*  Function: GetCurrentSegment
    Getter of current segment. If segment is not determined then it should be
     the value of -1, otherwise it is the index of the segment interpreted
     by the client
    */
    int GetCurrentSegment();
    /*  Function: CheckIfAnyMovesLeft
      Verify if there are any valid moves left. If not, the game should not
      be continued. Checks if available moves where inner board was not won
      has any value anywhere.
      */
    bool CheckIfAnyMovesLeft();
};

#endif //ULTIMATETICTACTOESERVER_GAMEENGINE_H
