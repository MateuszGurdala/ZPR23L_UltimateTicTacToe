
#include <memory>
#include <sstream>
#include "../../include/gameengine/GameEngine.hpp"
#include "../../include/helpers/BoardIndexConverter.hpp"

GameEngine::GameEngine(std::unique_ptr<MainBoard> mainBoard) : mainBoard(std::move(mainBoard)) {
    availableOuterBoardMoves = initializeAvailableSingleBoardMoves();
    allAvailableBoardMoves = initializeAvailableInnerBoardMoves();
}

std::vector<Point> GameEngine::initializeAvailableSingleBoardMoves() {
    unsigned int boardSize = GetBoardSize();
    std::vector<Point> availableMoves;
    availableMoves.reserve(boardSize*boardSize);
    for (unsigned int x = 0; x < boardSize; x++) {
        for (unsigned int y = 0; y < boardSize; y++) {
            availableMoves.emplace_back(x, y);
        }
    }
    return availableMoves;
}

std::vector<std::vector<Point>> GameEngine::initializeAvailableInnerBoardMoves() {
    unsigned int boardSize = GetBoardSize();
    std::vector<std::vector<Point>> availableMoves;
    availableMoves.reserve(boardSize*boardSize);
    for (unsigned int n = 0; n < boardSize*boardSize; n++) {
        availableMoves.emplace_back(initializeAvailableSingleBoardMoves());
    }
    return availableMoves;
}


void GameEngine::HandleMove(Point& boardCoordinates, Point& innerCoordinates, char figure) {
    mainBoard->MakeMove(boardCoordinates,innerCoordinates,figure);
    unsigned int boardSize = GetBoardSize();
    unsigned int innerBoardIndex = BoardIndexConverter::PointToIndex(boardCoordinates,boardSize);
    removePointFromAllAvailableMoves(innerBoardIndex, innerCoordinates);
}


bool GameEngine::CheckForLocalWinner(Point& mainBoardCoordinates, Point& innerBoardCellCoordinates, char figure) {
    auto& innerBoard = mainBoard->GetInnerBoard(mainBoardCoordinates);
    auto figuresInPattern = innerBoard->GetHorizontalValues(innerBoardCellCoordinates);
    if(AreAllValuesTheSame(figuresInPattern))
    {
        mainBoard->AddWinnerOfInnerBoard(mainBoardCoordinates, figure);
        removePointFromOuterAvailableMoves(mainBoardCoordinates);
        return true;
    }
    figuresInPattern = innerBoard->GetVerticalValues(innerBoardCellCoordinates);
    if(AreAllValuesTheSame(figuresInPattern))
    {
        removePointFromOuterAvailableMoves(mainBoardCoordinates);
        mainBoard->AddWinnerOfInnerBoard(mainBoardCoordinates, figure);
        return true;
    }
    figuresInPattern = innerBoard->GetLeftDiagonalValues(innerBoardCellCoordinates);
    if(AreAllValuesTheSame(figuresInPattern))
    {
        mainBoard->AddWinnerOfInnerBoard(mainBoardCoordinates, figure);
        removePointFromOuterAvailableMoves(mainBoardCoordinates);
        return true;
    }
    figuresInPattern = innerBoard->GetRightDiagonalValues(innerBoardCellCoordinates);
    if(AreAllValuesTheSame(figuresInPattern))
    {
        mainBoard->AddWinnerOfInnerBoard(mainBoardCoordinates, figure);
        removePointFromOuterAvailableMoves(mainBoardCoordinates);
        return true;
    }
    return false;
}
bool GameEngine::CheckForGlobalWinner(Point& changedWinnerBoardCellCoordinates) {
    auto figuresInPattern = mainBoard->GetWinnerBoard().GetHorizontalValues(changedWinnerBoardCellCoordinates);
    if(AreAllValuesTheSame(figuresInPattern))
    {
        return true;
    }
    figuresInPattern = mainBoard->GetWinnerBoard().GetVerticalValues(changedWinnerBoardCellCoordinates);
    if(AreAllValuesTheSame(figuresInPattern))
    {
        return true;
    }
    figuresInPattern = mainBoard->GetWinnerBoard().GetLeftDiagonalValues(changedWinnerBoardCellCoordinates);
    if(AreAllValuesTheSame(figuresInPattern))
    {
        return true;
    }
    figuresInPattern = mainBoard->GetWinnerBoard().GetRightDiagonalValues(changedWinnerBoardCellCoordinates);
    if(AreAllValuesTheSame(figuresInPattern))
    {
        return true;
    }
    return false;
}

bool GameEngine::AreAllValuesTheSame(const std::vector<char>& values) {
    auto it = std::adjacent_find(values.begin(), values.end(), std::not_equal_to<>());
    return it == values.end();
}

std::vector<Point> &GameEngine::GetAvailableOuterBoardMoves() {
    return availableOuterBoardMoves;
}

std::vector<std::vector<Point>> &GameEngine::GetAvailableInnerBoardMoves() {
    return allAvailableBoardMoves;
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

std::string GameEngine::PickSegmentAsJson(bool isNested, Point& segment, bool isValid){

    std::stringstream ss;
    if(!isNested)
    {
        ss << "{";
    }
    ss << "\"moveResponse\":";
    ss << "{";
    unsigned int boardSize = GetBoardSize();
    ss << "\"outerBoardIndex\":" << "\"" <<  BoardIndexConverter::PointToIndex(segment,boardSize) << "\",";
    ss << "\"innerBoardIndex\":" << "\"" <<  BoardIndexConverter::PointToIndex(segment,boardSize) << "\",";
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

void GameEngine::removePointFromOuterAvailableMoves(Point &pointToRemove) {
    unsigned int x = pointToRemove.x;
    unsigned int y = pointToRemove.y;
    availableOuterBoardMoves.erase(std::remove_if(availableOuterBoardMoves.begin(), availableOuterBoardMoves.end(),
                                        [x, y](const Point& point) {
                                            return (point.x == x && point.y == y);
                                        }), availableOuterBoardMoves.end());
}

void GameEngine::removePointFromAllAvailableMoves(unsigned int innerBoardIndex, Point &pointofInnerBoardToRemove) {
    auto& innerBoard = allAvailableBoardMoves[innerBoardIndex];
    unsigned int x = pointofInnerBoardToRemove.x;
    unsigned int y = pointofInnerBoardToRemove.y;
    innerBoard.erase(std::remove_if(innerBoard.begin(), innerBoard.end(),
                                                  [x, y](const Point& point) {
                                                      return (point.x == x && point.y == y);
                                                  }), innerBoard.end());
}
