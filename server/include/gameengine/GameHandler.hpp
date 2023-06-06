#ifndef ULTIMATETICTACTOESERVER_GAMEHANDLER_H
#define ULTIMATETICTACTOESERVER_GAMEHANDLER_H

#include "../entities/HumanPlayer.hpp"
#include "../entities/Player.hpp"
#include "GameEngine.hpp"
#include "GameStage.hpp"
#include <memory>

/*  Class: GameHandler
    Wrapper class for game logic which also links players with the game.
    It holds the logic of performing turn and invokes
    methods of gameEngine. It also holds the game state.
    Links logic classes, so they can be accessed in Http Handler.
    Creates all json strings that can be further interpreted by client.
    See also:
    <GameEngine>, <HttpHandler>
 */
class GameHandler {
private:
  std::unique_ptr<HumanPlayer> hostPlayer;
  std::unique_ptr<Player> secondPlayer;
  std::unique_ptr<GameEngine> gameEngine;
  bool isHostTurn = false;
  bool isSecondPlayerComputer;
  std::unique_ptr<GameStage> currentGameState;
  /*  Function: startGame
  Function that initializes elements of the handler like, game engine, players.
   If the game is against computer and the computer has the first move,
   it calls the performTurn on first simulated move.
    */
  void startGame(unsigned int boardSize, const std::string &hostName,
                 char hostSymbol, bool isPlayerVsComputer = true,
                 const std::string &guestName = "");
  /*  Function: updateGameStage
Helper method used inside performTurn method, used to determine what
   should be next stage of the game.
  boardCoordinates - Point (x,y) coordinates of the chosen inner board
  innerCoordinates - Point (x,y) chosen cell inside inner board
        */
  void updateGameStage(Point &outerBoardCoordinates, Point &innerCoordinates);

public:
  /*  Function: performMoveValidation
Checks if move performed by player was valid. Returns true if move was valid.
  Parameters:
    boardCoordinates - Point (x,y) coordinates of the chosen inner board
    innerCoordinates - Point (x,y) chosen cell inside inner board
          */
  bool performMoveValidation(Point boardCoordinates, Point innerCoordinates);
  /*  Function: performTurn
  Performs turn based on the provided coordinates. Handles the move,
   changes the turn, updates status of the game and calls game engine
   logic. Executes again with simulated coordinated if game is against computer

Parameters:
  boardCoordinates - Point (x,y) coordinates of the chosen inner board
  innerCoordinates - Point (x,y) chosen cell inside inner board
        */
  void performTurn(Point boardCoordinates, Point innerCoordinates);
  GameHandler(std::unique_ptr<HumanPlayer> hostPlayer,
              std::unique_ptr<Player> secondPlayer,
              std::unique_ptr<GameEngine> gameEngine, bool isPlayerVsComputer);
  /*  Constructor: GameHandler
  The main constructor of Game Handler expects that
   the size of board, symbol of the host and boolean if the game is against
  computer will be provided in order to call the startGame method. Alternative
  constructor expects that objects used in game handler are already created
  */
  GameHandler(unsigned int boardSize, char hostSymbol, bool isPlayerVsComputer,
              const std::string &hostName = "Host",
              const std::string &guestName = "Guest");

  std::string gameStateAsJson();
  std::string endGameAsJson(bool isPlayerSurrender);
  std::string createGameAsJson(bool isSuccess);
  std::string moveAsJson(bool isNested, std::array<Point, 2> move,
                         bool isValid);
  std::string pickSegmentAsJson(bool isNested, Point &segment, bool isValid);
  std::string winnerBoardAsJson();
  std::string boardStateAsJson();
  std::string getGameStage();
  int getSegmentIndex();
};

#endif // ULTIMATETICTACTOESERVER_GAMEHANDLER_H
