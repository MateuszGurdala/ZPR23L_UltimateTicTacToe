

#ifndef ULTIMATETICTACTOESERVER_COMPUTERPLAYER_HPP
#define ULTIMATETICTACTOESERVER_COMPUTERPLAYER_HPP

#include "BoardBase.hpp"
#include "Player.hpp"
#include <array>
#include <random>
#include <vector>

/*  Class: ComputerPlayer
    Class of a player handled by computer.
    Class was planned to be expanded if we managed to implement more
    advanced AI.
    See Also:
      <Player>
 */
class ComputerPlayer : public Player {
private:
public:
  /*  Constructor: ComputerPlayer
      Constructor which takes symbol which computer
      player will use during game.
  */
  ComputerPlayer(char symbol);
};

#endif // ULTIMATETICTACTOESERVER_COMPUTERPLAYER_HPP
