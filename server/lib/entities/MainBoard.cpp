#include <iostream>
#include "../../include/entities/MainBoard.h"

MainBoard::MainBoard(int boardSize) : BoardBase(boardSize) {
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

void MainBoard::AddWinnerOfInnerBoard(Point coordinates, char figure) {
    VerifyFigure(figure);
    VerifyCoordinates(coordinates);
    if(winnerBoard[coordinates.x][coordinates.y] != ' ')
    {
        throw std::invalid_argument("given given cell is already filled");
    }
    winnerBoard[coordinates.x][coordinates.y] = figure;
}