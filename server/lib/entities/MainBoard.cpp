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
}

void MainBoard::Print() const {
    for (const auto& row : mainPlayBoard) {
        for (const auto& innerBoard : row) {
            std::cout << innerBoard->ToString();
        }
        std::cout << "\n";
    }
}