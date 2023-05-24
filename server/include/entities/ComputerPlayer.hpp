

#ifndef ULTIMATETICTACTOESERVER_COMPUTERPLAYER_HPP
#define ULTIMATETICTACTOESERVER_COMPUTERPLAYER_HPP

#include <array>
#include "Player.hpp"
#include "BoardBase.hpp"
#include <vector>
#include <random>

/*  Class: ComputerPlayer
    Class of a player handled by computer. Main purpose of class is to create player and process player interaction with board.
    Also, the class will handle minmax algorithm.
 */
class ComputerPlayer : public Player {
private:
    /*  Function: SimulateMove
    Simulates move of real player. Currently, it chooses point randomly. In the future it will choose
     it based on the MINMAX algorithm.

    Parameters:

        availableMoves - Vector of Points which are available for algorithm to choose.
    Returns:
        Point chosen by algorithm.
    See Also:
      <HumanPlayer>, <Player>, <Point>
    */
    Point& SimulateMove(const std::vector<Point>& availableMoves);
public:

    /*  Function: ChooseMove
    Simulates move of real player. Currently, it chooses point randomly. In the future it will choose
     it based on the MINMAX algorithm.

    Parameters:

        availableOuterBoardMoves - Vector of Points which points to outer board which was not won yet.
        allAvailableBoardMoves - Vector of Points of board inside outer board which indicates which cell is available to place
                                    figure.
        boardSize - size of game board
     Returns:
        Array of 2 points. First point is coordinate of outer board and the second one is the cell of board inside it.
    See Also:
      <HumanPlayer>, <Player>, <Point>
    */
    std::array<Point, 2> ChooseMove(const std::vector<Point>& availableOuterBoardMoves,
                                    std::vector<std::vector<Point>> availableInnerBoardMoves, unsigned int boardSize) override;

    /*  Constructor: ComputerPlayer

        Constructor which takes symbol which computer player will use during game.
    */
    ComputerPlayer(char symbol);
};

#endif //ULTIMATETICTACTOESERVER_COMPUTERPLAYER_HPP
