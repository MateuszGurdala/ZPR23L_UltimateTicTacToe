#include <sstream>
#include "../../include/gameengine/GameHandler.hpp"
#include "../../include/entities/ComputerPlayer.hpp"

GameHandler::GameHandler(std::unique_ptr <HumanPlayer> hostPlayer, std::unique_ptr <Player> secondPlayer,
                         std::unique_ptr <GameEngine> gameEngine)
                         : hostPlayer(std::move(hostPlayer)), secondPlayer(std::move(secondPlayer)),
                         gameEngine(std::move(gameEngine)) {}

GameHandler::GameHandler()
{
    startGame();
}

void GameHandler::startGame() {
    hostPlayer = std::make_unique<HumanPlayer>('X', std::string("testHost"));
    secondPlayer = std::make_unique<ComputerPlayer>('O');

    auto mainBoard = std::make_unique<MainBoard>(3);
    gameEngine = std::make_unique<GameEngine>(std::move(mainBoard));
}

//TODO
bool GameHandler::CheckIfGameEnd() {
    return false;
}

std::array<Point, 2> GameHandler::ChooseCoordinatesOfMove(){
    std::array<Point, 2> target{};
    if(isHostTurn)
    {
        target = hostPlayer->ChooseMove(gameEngine->getAvailableOuterBoardMoves(),
                                        gameEngine->getAvailableInnerBoardMoves(), gameEngine->GetBoardSize());
    }
    else
    {
       target = secondPlayer->ChooseMove(gameEngine->getAvailableOuterBoardMoves(),
                                         gameEngine->getAvailableInnerBoardMoves(), gameEngine->GetBoardSize());
    }
    return target;
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
    isHostTurn = !isHostTurn;
}

//TODO consider moving jsons with communication to other class
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
