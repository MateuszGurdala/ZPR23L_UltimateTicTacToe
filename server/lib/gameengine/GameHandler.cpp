#include <sstream>

#include "../../include/entities/ComputerPlayer.hpp"
#include "../../include/gameengine/GameHandler.hpp"
#include "../../include/helpers/BoardIndexConverter.hpp"

GameHandler::GameHandler(std::unique_ptr<HumanPlayer> hostPlayer,
                         std::unique_ptr<Player> secondPlayer,
                         std::unique_ptr<GameEngine> gameEngine)
    : hostPlayer(std::move(hostPlayer)), secondPlayer(std::move(secondPlayer)),
      gameEngine(std::move(gameEngine)) {
  currentGameState = std::make_unique<GameStage>();
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
  currentGameState->SetGameStage("Player X Turn, choose segment");
  if(isSecondPlayerComputer && !isHostTurn){
    std::array<Point, 2> simulatedCoordinates = gameEngine->HandleComputerMove();
    PerformTurn(simulatedCoordinates[0], simulatedCoordinates[1]);
  }
}

bool GameHandler::PerformMoveValidation(Point boardCoordinates,
                                        Point innerCoordinates) {
  unsigned int boardSize = gameEngine->GetBoardSize();
  unsigned int winnerBoardIndex =
      BoardIndexConverter::PointToIndex(boardCoordinates, boardSize);
  auto const availableMoves = gameEngine->GetAvailableInnerBoardMoves();
  bool isPointValid = std::any_of(
      availableMoves[winnerBoardIndex].begin(),
      availableMoves[winnerBoardIndex].end(), [&](const Point &point) {
        return point.x == innerCoordinates.x && point.y == innerCoordinates.y;
      });
  return isPointValid;
}
int GameHandler::GetSegmentIndex(){
  return gameEngine->GetCurrentSegment();
}


void GameHandler::PerformTurn(Point boardCoordinates, Point innerCoordinates) {
  char currentFigure;
  if (isHostTurn) {
    currentFigure = hostPlayer->GetSymbol();
  } else {
    currentFigure = secondPlayer->GetSymbol();
  }
  gameEngine->HandleMove(boardCoordinates, innerCoordinates, currentFigure);
  gameEngine->CheckForLocalWinner(boardCoordinates, innerCoordinates,
                                  currentFigure);
  isHostTurn = !isHostTurn;
  updateGameStage(boardCoordinates, innerCoordinates);
  gameEngine->UpdateCurrentLegalMoves(innerCoordinates);
  if(isSecondPlayerComputer && !isHostTurn){
    std::array<Point, 2> simulatedCoordinates = gameEngine->HandleComputerMove();
    PerformTurn(simulatedCoordinates[0], simulatedCoordinates[1]);
  }
}

void GameHandler::updateGameStage(Point &outerBoardCoordinates,
                                  Point &innerCoordinates) {
  if (gameEngine->CheckForGlobalWinner(outerBoardCoordinates)) {
    currentGameState->SetGameStage("Game is Finished");
    return;
  }
  char currentSymbol;
  if (isHostTurn) {
    currentSymbol = hostPlayer->GetSymbol();
  } else {
    currentSymbol = secondPlayer->GetSymbol();
  }
  std::string symbolString(1, currentSymbol);
  if (gameEngine->IsSegmentChoosen(innerCoordinates)) {
    currentGameState->SetGameStage("Player " + symbolString +
                                   " Turn, choose segment");
    return;
  } else {
    currentGameState->SetGameStage("Player " + symbolString + " Turn");
    return;
  }
}

std::string GameHandler::GameStateAsJson() {
  std::stringstream ss;
  ss << "{";
  ss << "\"hostPlayer\":";
  ss << "{";
  ss << "\"name\":"
     << "\"" << hostPlayer->GetName() << "\",";
  ss << "\"symbol\":"
     << "\"" << hostPlayer->GetSymbol() << "\",";
  ss << "},";
  ss << "\"guestPlayer\":";
  ss << "{";
  ss << "\"name\":"
     << "\"" << secondPlayer->GetName() << "\",";
  ss << "\"symbol\":"
     << "\"" << secondPlayer->GetSymbol() << "\",";
  ss << "},";
  ss << "\"currentTurn\":";
  ss << "{";
  if (isHostTurn) {
    ss << "\"nowPlaying\":"
       << "\"" << hostPlayer->GetSymbol() << "\"";
  } else {
    ss << "\"nowPlaying\":"
       << "\"" << secondPlayer->GetSymbol() << "\"";
  }
  ss << "}";
  gameEngine->GetWinnerBoardAsJson(true);
  ss << "}";
  return ss.str();
}
std::string GameHandler::EndGameAsJson(bool isPlayerSurrender) {
  std::stringstream ss;
  std::string invokerName;
  std::string idlePlayerName;
  if (isHostTurn) {
    invokerName = hostPlayer->GetName();
    idlePlayerName = secondPlayer->GetName();
  } else {
    invokerName = secondPlayer->GetName();
    idlePlayerName = hostPlayer->GetName();
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

std::string GameHandler::CreateGameAsJson(bool isSuccess) {
  std::stringstream ss;
  ss << "{";
  ss << "\"createGameResponse\":";
  ss << "{";
  if (isSuccess) {
    ss << "\"isSuccess\":true"
       << "\",";
    ss << "\"hostName\":"
       << "\"" << hostPlayer->GetName() << "\",";
    ss << "\"hostSymbol\":"
       << "\"" << hostPlayer->GetSymbol() << "\",";
    ss << "\"guestName\":"
       << "\"" << secondPlayer->GetName() << "\",";
    ss << "\"guestSymbol\":"
       << "\"" << secondPlayer->GetSymbol() << "\",";
    ss << "\"boardSize\":"
       << "\"" << gameEngine->GetBoardSize() << "\"";
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

std::string GameHandler::BoardStateAsJson() {
  return gameEngine->GetBoardAsJson(false);
}

std::string GameHandler::WinnerBoardAsJson() {
  return gameEngine->GetWinnerBoardAsJson(false);
}

std::string GameHandler::MoveAsJson(bool isNested, std::array<Point, 2> move,
                                    bool isValid) {
  std::stringstream ss;
  if (!isNested) {
    ss << "{";
  }
  ss << "\"moveResponse\":";
  ss << "{";
  unsigned int boardSize = gameEngine->GetBoardSize();
  ss << "\"outerBoardIndex\":"
     << "\"" << BoardIndexConverter::PointToIndex(move[0], boardSize) << "\",";
  ss << "\"innerBoardIndex\":"
     << "\"" << BoardIndexConverter::PointToIndex(move[1], boardSize) << "\",";
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

std::string GameHandler::PickSegmentAsJson(bool isNested, Point &segment,
                                           bool isValid) {

  std::stringstream ss;
  if (!isNested) {
    ss << "{";
  }
  ss << "\"moveResponse\":";
  ss << "{";
  unsigned int boardSize = gameEngine->GetBoardSize();
  ss << "\"outerBoardIndex\":"
     << "\"" << BoardIndexConverter::PointToIndex(segment, boardSize) << "\",";
  ss << "\"innerBoardIndex\":"
     << "\"" << BoardIndexConverter::PointToIndex(segment, boardSize) << "\",";
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

std::string GameHandler::GetGameStage() {
  return currentGameState->GetCurrentGameStage();
}
