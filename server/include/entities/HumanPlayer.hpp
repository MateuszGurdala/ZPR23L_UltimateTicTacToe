#ifndef ULTIMATETICTACTOESERVER_HUMANPLAYER_HPP
#define ULTIMATETICTACTOESERVER_HUMANPLAYER_HPP

#include "Player.hpp"

/*  Class: HumanPlayer
    Class of a player handled by real person. Main purpose of class is to create player and process player interaction with board
 */
class HumanPlayer : public Player {
private:
public:
    /*  Constructor: ComputerPlayer
    Constructor which takes symbol which player will use during game and his nickname.
    */
    HumanPlayer(char symbol,std::string name);
    /*  Function: ChooseMove
    TODO this function will process move of human player

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
};

#endif //ULTIMATETICTACTOESERVER_HUMANPLAYER_HPP
