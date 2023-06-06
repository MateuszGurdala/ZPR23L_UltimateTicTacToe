#ifndef ULTIMATETICTACTOESERVER_GAMESTAGE_H
#define ULTIMATETICTACTOESERVER_GAMESTAGE_H

#include <array>
#include <string>

/*  Class: GameStage
    Helper class used in handler responsible for managing current stage of the
    game. Stage of the game is allowing the client to see at what state the
    game is. There are finite number of valid stages that can be set and
    interpreted by the client.
    See Also:
    <GameHandler>
*/
class GameStage {
private:
  std::array<std::string, 6> validStages = {
      "Unknown",
      "Player X Turn",
      "Player O Turn",
      "Player X Turn, choose segment",
      "Player O Turn, choose segment",
      "Game is Finished",
  };
  std::string currentGameStage;

public:
  /*  Function: setGameStage
      Sets new game stage and checks if it is a valid game stage.
   */
  void setGameStage(const std::string &newGameStatus);
  /*  Function: getCurrentGameStage
      Getter for current game stage
   */
  std::string getCurrentGameStage();
};

#endif // ULTIMATETICTACTOESERVER_GAMESTAGE_H
