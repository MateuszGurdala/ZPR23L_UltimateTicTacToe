
#include <memory>
#include <sstream>
#include "../../include/gameengine/GameEngine.hpp"
#include "../../include/helpers/BoardIndexConverter.hpp"

GameEngine::GameEngine(std::unique_ptr <MainBoard> mainBoard) : mainBoard(std::move(mainBoard)) {
    unsigned int boardSize = this->mainBoard->GetBoardSize();
    availableOuterBoardMoves = InitializeAvailableSingleBoardMoves(boardSize);
    availableInnerBoardMoves = InitializeAvailableInnerBoardMoves(boardSize);
}

std::vector<Point> GameEngine::InitializeAvailableSingleBoardMoves(unsigned int boardSize) {
    std::vector<Point> availableMoves;
    availableMoves.reserve(boardSize*boardSize);
    for (unsigned int x = 0; x < boardSize; x++) {
        for (unsigned int y = 0; y < boardSize; y++) {
            availableMoves.emplace_back(Point(x, y));
        }
    }
    return availableMoves;
}

std::vector<std::vector<Point>> GameEngine::InitializeAvailableInnerBoardMoves(unsigned int boardSize) {
    std::vector<std::vector<Point>> availableMoves;
    availableMoves.reserve(boardSize*boardSize);
    for (unsigned int n = 0; n < boardSize*boardSize; n++) {
        availableMoves.emplace_back(InitializeAvailableSingleBoardMoves(boardSize));
    }
    return availableMoves;
}


void GameEngine::HandleMove(Point& boardCoordinates, Point& innerCoordinates, char figure) {
    mainBoard->MakeMove(boardCoordinates,innerCoordinates,figure);
}


//TODO implement
bool GameEngine::CheckLocalWinner() {
    return false;
}

//TODO implement
bool GameEngine::CheckGlobalWinner() {
    return false;
}

std::vector<Point> &GameEngine::getAvailableOuterBoardMoves() {
    return availableOuterBoardMoves;
}

std::vector<std::vector<Point>> &GameEngine::getAvailableInnerBoardMoves() {
    return availableInnerBoardMoves;
}

unsigned int GameEngine::GetBoardSize() {
    return mainBoard->GetBoardSize();
}



std::string GameEngine::GetWinnerBoardAsJson(bool isNested){
    return mainBoard->WinnerBoardToJson(isNested);
}

std::string GameEngine::MoveAsJson(bool isNested, std::array<Point,2> move, bool isValid) {
    std::stringstream ss;
    if(!isNested)
    {
        ss << "{";
    }
    ss << "\"moveResponse\":";
    ss << "{";
    unsigned int boardSize = GetBoardSize();
    ss << "\"outerBoardIndex\":" << "\"" <<  BoardIndexConverter::PointToIndex(move[0],boardSize) << "\",";
    ss << "\"innerBoardIndex\":" << "\"" <<  BoardIndexConverter::PointToIndex(move[1],boardSize) << "\",";
    if(isValid)
    {
        ss << "\"isMoveValid\":" <<  "true" ;
    }
    else
    {
        ss << "\"isMoveValid\":" <<  "false" ;
    }
    ss << "}";
    if(!isNested)
    {
        ss << "}";
    }
    return ss.str();
}
