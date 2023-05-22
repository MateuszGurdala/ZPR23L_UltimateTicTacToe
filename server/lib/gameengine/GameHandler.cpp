#include <sstream>
#include "../../include/gameengine/GameHandler.hpp"
#include "../../include/entities/ComputerPlayer.hpp"
#include "../../include/helpers/BoardIndexConverter.hpp"

GameHandler::GameHandler(std::unique_ptr <HumanPlayer> hostPlayer, std::unique_ptr <Player> secondPlayer,
                         std::unique_ptr <GameEngine> gameEngine)
                         : hostPlayer(std::move(hostPlayer)), secondPlayer(std::move(secondPlayer)),
                         gameEngine(std::move(gameEngine)) {}

GameHandler::GameHandler(unsigned int boardSize, const std::string& hostName, char hostSymbol, bool isPlayerVsComputer, const std::string& guestName)
{
    startGame(boardSize, hostName, hostSymbol, isPlayerVsComputer, guestName);
}

void GameHandler::startGame(unsigned int boardSize, const std::string& hostName, char hostSymbol, bool isPlayerVsComputer, const std::string& guestName) {
    if(isPlayerVsComputer && !guestName.empty()) {
        throw std::invalid_argument("Computer player cannot have a nickname.");
    }
    if(hostName.empty())
    {
        throw std::invalid_argument("Client must have a name.");
    }
    if(hostSymbol != 'X' && hostSymbol != 'O')
    {
        throw std::invalid_argument("Invalid symbol of Host");
    }
    char guestSymbol;
    if(hostSymbol == 'O')
    {
        guestSymbol = 'X';
        isHostTurn = false;
    }
    else
    {
        guestSymbol = 'O';
        isHostTurn = true;
    }
    hostPlayer = std::make_unique<HumanPlayer>(hostSymbol, hostName);

    if(isPlayerVsComputer)
    {
        secondPlayer = std::make_unique<ComputerPlayer>(guestSymbol);
    }
    else
    {
        secondPlayer = std::make_unique<HumanPlayer>(guestSymbol, guestName);
    }
    auto mainBoard = std::make_unique<MainBoard>(boardSize);
    gameEngine = std::make_unique<GameEngine>(std::move(mainBoard));
}

//TODO
void GameHandler::handleGameEnd() {
    currentGameState->SetGameStatus("Finished");
}

std::array<Point, 2> GameHandler::ChooseCoordinatesOfMove(){
    std::array<Point, 2> target;
    if(isHostTurn)
    {
        target = hostPlayer->ChooseMove(gameEngine->GetAvailableOuterBoardMoves(),
                                        gameEngine->GetAvailableInnerBoardMoves(), gameEngine->GetBoardSize());
    }
    else
    {
       target = secondPlayer->ChooseMove(gameEngine->GetAvailableOuterBoardMoves(),
                                         gameEngine->GetAvailableInnerBoardMoves(), gameEngine->GetBoardSize());
    }
    return target;
}

bool GameHandler::PerformMoveValidation(Point boardCoordinates, Point innerCoordinates){
    unsigned int boardSize = gameEngine->GetBoardSize();
    unsigned int winnerBoardIndex = BoardIndexConverter::PointToIndex(boardCoordinates, boardSize);
    auto const availableMoves = gameEngine->GetAvailableInnerBoardMoves();
    if(availableMoves[winnerBoardIndex].empty())
    {
        return false;
    }
    return true;

}


void GameHandler::PerformTurn(Point boardCoordinates, Point innerCoordinates) {

    char currentFigure;
    if(isHostTurn)
    {
        currentFigure = hostPlayer->GetSymbol();
    }
    else
    {
        currentFigure = secondPlayer->GetSymbol();
    }
    gameEngine->HandleMove(boardCoordinates, innerCoordinates, currentFigure);
    gameEngine->CheckForLocalWinner(boardCoordinates, innerCoordinates, currentFigure);
    if(gameEngine->CheckForGlobalWinner(boardCoordinates))
    {
        handleGameEnd();
    }
    isHostTurn = !isHostTurn;
    gameEngine->UpdateCurrentLegalMoves(innerCoordinates, boardCoordinates);
}

std::string GameHandler::GameStateAsJson() {
    std::stringstream ss;
    ss << "{";
        ss << "\"hostPlayer\":";
        ss << "{";
            ss << "\"name\":" << "\"" << hostPlayer->GetName() << "\",";
            ss << "\"symbol\":" << "\"" << hostPlayer->GetSymbol() << "\",";
            ss << "\"points\":" << "\"" << hostPlayer->GetPoints() << "\"";
        ss << "},";
            ss << "\"guestPlayer\":";
        ss << "{";
            ss << "\"name\":" << "\"" << secondPlayer->GetName() << "\",";
            ss << "\"symbol\":" << "\"" << secondPlayer->GetSymbol()<< "\",";
            ss << "\"points\":" << "\"" << secondPlayer->GetPoints() << "\"";
        ss << "},";
            ss << "\"currentTurn\":";
        ss << "{";
        if(isHostTurn)
        {
            ss << "\"nowPlaying\":" << "\"" << hostPlayer->GetSymbol()<< "\"" ;
        }
        else
        {
            ss << "\"nowPlaying\":" << "\"" << secondPlayer->GetSymbol() << "\"";
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
    if(isHostTurn)
    {
        invokerName = hostPlayer->GetName();
        idlePlayerName = secondPlayer->GetName();
    }
    else
    {
        invokerName = secondPlayer->GetName();
        idlePlayerName = hostPlayer->GetName();
    }
    ss << "{";
        ss << "\"endGame\":";
        ss << "{";
            if(isPlayerSurrender)
            {
                ss << "\"whoEndedGame\":" << "\"" << idlePlayerName << "\"," ;
                ss << "\"winner\":" << "\"" << "true" << "\"" ;

            }
            else
            {
                ss << "\"whoEndedGame\":" << "\"" << invokerName << "\",";
                ss << "\"winner\":" << "\"" << "false" << "\"" ;

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
            if(isSuccess)
            {
                ss << "\"isSuccess\":true" << "\"," ;
                ss << "\"hostName\":" << "\"" << hostPlayer->GetName() << "\"," ;
                ss << "\"hostSymbol\":" << "\"" << hostPlayer->GetSymbol() << "\"," ;
                ss << "\"guestName\":" << "\"" << secondPlayer->GetName() << "\"," ;
                ss << "\"guestSymbol\":" << "\"" << secondPlayer->GetSymbol() << "\",";
                ss << "\"boardSize\":" << "\"" <<  gameEngine->GetBoardSize() << "\"";
            }
            else
            {
                ss << "\"isSuccess\":false" << "\"," ;
                ss << "\"hostName\":" << "\"" << "" << "\"," ;
                ss << "\"hostSymbol\":" << "\"" << "" << "\"," ;
                ss << "\"guestName\":" << "\"" << "" << "\"," ;
                ss << "\"guestSymbol\":" << "\"" << "" << "\",";
                ss << "\"boardSize\":" << "\"" <<  "" << "\"";
            }
        ss << "}";
    ss << "}";
    return ss.str();
}
