#include <iostream>
#include "../../include/entities/MainBoard.hpp"

MainBoard::MainBoard(int boardSize) : BoardBase(boardSize), winnerBoard(new std::unique_ptr<char[]>[boardSize]){
    mainPlayBoard.resize(boardSize);
    for (auto& row : mainPlayBoard) {
        row.resize(boardSize);
    }
    FillBoard();
}

void MainBoard::FillBoard() {
    for (auto& row : mainPlayBoard) {
        for (int j = 0; j < boardSize; j++) {
            row[j] = std::make_unique<InnerBoard>(boardSize);
        }
    }
    for (int i = 0; i < boardSize; i++) {
        winnerBoard[i] = std::make_unique<char[]>(boardSize);
        for (int j = 0; j < boardSize; j++) {
            winnerBoard[i][j] = ' ';
        }
    }
}

void MainBoard::Print() const {
    for (const auto& row : mainPlayBoard) {
        for (const auto& innerBoard : row) {
            std::cout << innerBoard->ToString();
        }
        std::cout << "\n";
    }
}

void MainBoard::AddWinnerOfInnerBoard(Point& coordinates, char& figure) {
    VerifyFigure(figure);
    VerifyCoordinates(coordinates);
    if(winnerBoard[coordinates.x][coordinates.y] != ' ')
    {
        throw std::invalid_argument("given given cell is already filled");
    }
    winnerBoard[coordinates.x][coordinates.y] = figure;
}

//TODO
/*auto MainBoard::GetInnerBoardVerticalValues(Point& playBoardCoordinates, Point& innerBoardRowAndColumn) {
    return nullptr;
}

auto MainBoard::GetInnerBoardRightDiagonalValues(Point& playBoardCoordinates, Point& innerBoardRowAndColumn) {
    return nullptr;
}

auto MainBoard::GetInnerBoardLeftDiagonalValues(Point& playBoardCoordinates, Point& innerBoardRowAndColumn) {
    return nullptr;
}

auto MainBoard::GetInnerBoarHorizontalValues(Point& playBoardCoordinates, Point& innerBoardRowAndColumn) {
    return nullptr;
}*/

void MainBoard::MakeMove(Point& boardCoordinates, Point& innerCoordinates, char& figure) {
    mainPlayBoard[boardCoordinates.x][boardCoordinates.y]->PlaceFigure(innerCoordinates, figure);
}
