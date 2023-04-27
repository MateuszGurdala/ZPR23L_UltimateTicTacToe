
#include <memory>
#include "../../include/gameengine/GameEngine.hpp"

GameEngine::GameEngine(std::unique_ptr <MainBoard> mainBoard) : mainBoard(std::move(mainBoard)) {
    int boardSize = this->mainBoard->GetBoardSize();
    availableOuterBoardMoves = InitializeAvailableSingleBoardMoves(boardSize);
    availableInnerBoardMoves = InitializeAvailableInnerBoardMoves(boardSize);
}

std::vector<Point> GameEngine::InitializeAvailableSingleBoardMoves(int boardSize) {
    std::vector<Point> availableMoves;
    availableMoves.reserve(boardSize*boardSize);
    for (int x = 0; x < boardSize; x++) {
        for (int y = 0; y < boardSize; y++) {
            availableMoves.emplace_back(Point(x, y));
        }
    }
    return availableMoves;
}

std::vector<std::vector<Point>> GameEngine::InitializeAvailableInnerBoardMoves(int boardSize) {
    std::vector<std::vector<Point>> availableMoves;
    availableMoves.reserve(boardSize*boardSize);
    for (int n = 0; n < boardSize*boardSize; n++) {
        availableMoves.emplace_back(InitializeAvailableSingleBoardMoves(boardSize));
    }
    return availableMoves;
}


void GameEngine::HandleMove(Point& boardCoordinates, Point& innerCoordinates, char figure) {
    mainBoard->MakeMove(boardCoordinates,innerCoordinates,figure);
}

void GameEngine::Print()
{
    mainBoard->Print();
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

int GameEngine::GetBoardSize() {
    return mainBoard->GetBoardSize();
}
