
#ifndef ULTIMATETICTACTOESERVER_PLAYER_HPP
#define ULTIMATETICTACTOESERVER_PLAYER_HPP

#include "BoardBase.hpp"
#include <array>
#include <string>
#include <vector>

/*  Class: Player
    Base class for tic-tac-toe players.

    See Also:
      <HumanPlayer>, <ComputerPlayer>
 */
class Player {
protected:
  char symbol;
  std::string name = "Player";

public:
  virtual ~Player() = default;
  Player(char symbol);
  std::string getName() const;
  char getSymbol() const;
};

#endif // ULTIMATETICTACTOESERVER_PLAYER_HPP
