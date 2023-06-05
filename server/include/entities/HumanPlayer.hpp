#ifndef ULTIMATETICTACTOESERVER_HUMANPLAYER_HPP
#define ULTIMATETICTACTOESERVER_HUMANPLAYER_HPP

#include "Player.hpp"

/*  Class: HumanPlayer
    Class of a player handled by real person.
    Human player can provide his nickname.
    See Also:
      <Player>
 */
class HumanPlayer : public Player {
private:
public:
    /*  Constructor: ComputerPlayer
    Constructor which takes symbol which player will use during game
     and his nickname.
    */
    HumanPlayer(char symbol,std::string name);
};

#endif //ULTIMATETICTACTOESERVER_HUMANPLAYER_HPP
