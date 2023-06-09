#include <sstream>

#include "../../include/entities/ComputerPlayer.hpp"
#include "../../include/gameengine/GameHandler.hpp"
#include "../../include/helpers/BoardIndexConverter.hpp"

GameHandler::GameHandler(std::unique_ptr<HumanPlayer> hostPlayer,
                         std::unique_ptr<Player> secondPlayer,
                         std::unique_ptr<GameEngine> gameEngine,
                         bool isPlayerVsComputer)
    : hostPlayer(std::move(hostPlayer)), secondPlayer(std::move(secondPlayer)),
      gameEngine(std::move(gameEngine)),
      isSecondPlayerComputer(isPlayerVsComputer) {
  currentGameState = std::make_unique<GameStage>();
  currentGameState->setGameStage("Player X Turn, choose segment");
  if (isSecondPlayerComputer && !isHostTurn) {
    std::array<Point, 2> simulatedCoordinates =
        this->gameEngine->handleComputerMove();
    performTurn(simulatedCoordinates[0], simulatedCoordinates[1]);
  }
}

GameHandler::GameHandler(unsigned int boardSize, char hostSymbol,
                         bool isPlayerVsComputer, const std::string &hostName,
                         const std::string &guestName) {
  currentGameState = std::make_unique<GameStage>();
  isSecondPlayerComputer = isPlayerVsComputer;
  startGame(boardSize, hostName, hostSymbol, isPlayerVsComputer, guestName);
}

void GameHandler::startGame(unsigned int boardSize, const std::string &hostName,
                            char hostSymbol, bool isPlayerVsComputer,
                            const std::string &guestName) {
  if (hostName.empty()) {
    throw std::invalid_argument("Client must have a name.");
  }
  if (hostSymbol != 'X' && hostSymbol != 'O') {
    throw std::invalid_argument("Invalid symbol of Host");
  }
  char guestSymbol;
  if (hostSymbol == 'O') {
    guestSymbol = 'X';
    isHostTurn = false;
  } else {
    guestSymbol = 'O';
    isHostTurn = true;
  }
  hostPlayer = std::make_unique<HumanPlayer>(hostSymbol, hostName);

  if (isPlayerVsComputer) {
    secondPlayer = std::make_unique<ComputerPlayer>(guestSymbol);
  } else {
    secondPlayer = std::make_unique<HumanPlayer>(guestSymbol, guestName);
  }
  auto mainBoard = std::make_unique<MainBoard>(boardSize);
  gameEngine = std::make_unique<GameEngine>(std::move(mainBoard));
  currentGameState->setGameStage("Player X Turn, choose segment");
  if (isSecondPlayerComputer && !isHostTurn) {
    std::array<Point, 2> simulatedCoordinates =
        gameEngine->handleComputerMove();
    performTurn(simulatedCoordinates[0], simulatedCoordinates[1]);
  }
}

bool GameHandler::performMoveValidation(Point boardCoordinates,
                                        Point innerCoordinates) {
  unsigned int boardSize = gameEngine->getBoardSize();
  unsigned int winnerBoardIndex =
      BoardIndexConverter::pointToIndex(boardCoordinates, boardSize);
  auto const availableMoves = gameEngine->getAvailableInnerBoardMoves();
  bool isPointValid = std::any_of(
      availableMoves[winnerBoardIndex].begin(),
      availableMoves[winnerBoardIndex].end(), [&](const Point &point) {
        return point.x == innerCoordinates.x && point.y == innerCoordinates.y;
      });
  return isPointValid;
}
int GameHandler::getSegmentIndex() { return gameEngine->getCurrentSegment(); }

void GameHandler::performTurn(Point boardCoordinates, Point innerCoordinates) {
  char currentFigure;
  if (isHostTurn) {
    currentFigure = hostPlayer->getSymbol();
  } else {
    currentFigure = secondPlayer->getSymbol();
  }
  gameEngine->handleMove(boardCoordinates, innerCoordinates, currentFigure);
  gameEngine->checkForLocalWinner(boardCoordinates, innerCoordinates,
                                  currentFigure);
  isHostTurn = !isHostTurn;
  updateGameStage(boardCoordinates, innerCoordinates);
  if (currentGameState->getCurrentGameStage() == "Game is Finished") {
    return;
  }
  gameEngine->updateCurrentLegalMoves(innerCoordinates);
  if (isSecondPlayerComputer && !isHostTurn) {
    std::array<Point, 2> simulatedCoordinates =
        gameEngine->handleComputerMove();
    performTurn(simulatedCoordinates[0], simulatedCoordinates[1]);
  }
}

void GameHandler::updateGameStage(Point &outerBoardCoordinates,
                                  Point &innerCoordinates) {
  if (gameEngine->checkForGlobalWinner(outerBoardCoordinates) ||
      !gameEngine->checkIfAnyMovesLeft()) {
    currentGameState->setGameStage("Game is Finished");
    return;
  }
  char currentSymbol;
  if (isHostTurn) {
    currentSymbol = hostPlayer->getSymbol();
  } else {
    currentSymbol = secondPlayer->getSymbol();
  }
  std::string symbolString(1, currentSymbol);
  if (!gameEngine->isSegmentChosen(innerCoordinates)) {
    currentGameState->setGameStage("Player " + symbolString +
                                   " Turn, choose segment");
    return;
  } else {
    currentGameState->setGameStage("Player " + symbolString + " Turn");
    return;
  }
}

std::string GameHandler::gameStateAsJson() {
  std::stringstream ss;
  ss << "{";
  ss << "\"hostPlayer\":";
  ss << "{";
  ss << "\"name\":"
     << "\"" << hostPlayer->getName() << "\",";
  ss << "\"symbol\":"
     << "\"" << hostPlayer->getSymbol() << "\",";
  ss << "},";
  ss << "\"guestPlayer\":";
  ss << "{";
  ss << "\"name\":"
     << "\"" << secondPlayer->getName() << "\",";
  ss << "\"symbol\":"
     << "\"" << secondPlayer->getSymbol() << "\",";
  ss << "},";
  ss << "\"currentTurn\":";
  ss << "{";
  if (isHostTurn) {
    ss << "\"nowPlaying\":"
       << "\"" << hostPlayer->getSymbol() << "\"";
  } else {
    ss << "\"nowPlaying\":"
       << "\"" << secondPlayer->getSymbol() << "\"";
  }
  ss << "}";
  gameEngine->getWinnerBoardAsJson(true);
  ss << "}";
  return ss.str();
}
std::string GameHandler::endGameAsJson(bool isPlayerSurrender) {
  std::stringstream ss;
  std::string invokerName;
  std::string idlePlayerName;
  if (isHostTurn) {
    invokerName = hostPlayer->getName();
    idlePlayerName = secondPlayer->getName();
  } else {
    invokerName = secondPlayer->getName();
    idlePlayerName = hostPlayer->getName();
  }
  ss << "{";
  ss << "\"endGame\":";
  ss << "{";
  if (isPlayerSurrender) {
    ss << "\"whoEndedGame\":"
       << "\"" << idlePlayerName << "\",";
    ss << "\"winner\":"
       << "\""
       << "true"
       << "\"";

  } else {
    ss << "\"whoEndedGame\":"
       << "\"" << invokerName << "\",";
    ss << "\"winner\":"
       << "\""
       << "false"
       << "\"";
  }
  ss << "}";
  ss << "}";
  return ss.str();
}

std::string GameHandler::createGameAsJson(bool isSuccess) {
  std::stringstream ss;
  ss << "{";
  ss << "\"createGameResponse\":";
  ss << "{";
  if (isSuccess) {
    ss << "\"isSuccess\":true"
       << "\",";
    ss << "\"hostName\":"
       << "\"" << hostPlayer->getName() << "\",";
    ss << "\"hostSymbol\":"
       << "\"" << hostPlayer->getSymbol() << "\",";
    ss << "\"guestName\":"
       << "\"" << secondPlayer->getName() << "\",";
    ss << "\"guestSymbol\":"
       << "\"" << secondPlayer->getSymbol() << "\",";
    ss << "\"boardSize\":"
       << "\"" << gameEngine->getBoardSize() << "\"";
  } else {
    ss << "\"isSuccess\":false"
       << "\",";
    ss << "\"hostName\":"
       << "\""
       << ""
       << "\",";
    ss << "\"hostSymbol\":"
       << "\""
       << ""
       << "\",";
    ss << "\"guestName\":"
       << "\""
       << ""
       << "\",";
    ss << "\"guestSymbol\":"
       << "\""
       << ""
       << "\",";
    ss << "\"boardSize\":"
       << "\""
       << ""
       << "\"";
  }
  ss << "}";
  ss << "}";
  return ss.str();
}

std::string GameHandler::boardStateAsJson() {
  return gameEngine->getBoardAsJson(false);
}

std::string GameHandler::winnerBoardAsJson() {
  return gameEngine->getWinnerBoardAsJson(false);
}

std::string GameHandler::moveAsJson(bool isNested, std::array<Point, 2> move,
                                    bool isValid) {
  std::stringstream ss;
  if (!isNested) {
    ss << "{";
  }
  ss << "\"moveResponse\":";
  ss << "{";
  unsigned int boardSize = gameEngine->getBoardSize();
  ss << "\"outerBoardIndex\":"
     << "\"" << BoardIndexConverter::pointToIndex(move[0], boardSize) << "\",";
  ss << "\"innerBoardIndex\":"
     << "\"" << BoardIndexConverter::pointToIndex(move[1], boardSize) << "\",";
  if (isValid) {
    ss << "\"isMoveValid\":"
       << "true";
  } else {
    ss << "\"isMoveValid\":"
       << "false";
  }
  ss << "}";
  if (!isNested) {
    ss << "}";
  }
  return ss.str();
}

std::string GameHandler::pickSegmentAsJson(bool isNested, Point &segment,
                                           bool isValid) {

  std::stringstream ss;
  if (!isNested) {
    ss << "{";
  }
  ss << "\"moveResponse\":";
  ss << "{";
  unsigned int boardSize = gameEngine->getBoardSize();
  ss << "\"outerBoardIndex\":"
     << "\"" << BoardIndexConverter::pointToIndex(segment, boardSize) << "\",";
  ss << "\"innerBoardIndex\":"
     << "\"" << BoardIndexConverter::pointToIndex(segment, boardSize) << "\",";
  if (isValid) {
    ss << "\"isMoveValid\":"
       << "true";
  } else {
    ss << "\"isMoveValid\":"
       << "false";
  }
  ss << "}";
  if (!isNested) {
    ss << "}";
  }
  return ss.str();
}

std::string GameHandler::getGameStage() {
  return currentGameState->getCurrentGameStage();
}
