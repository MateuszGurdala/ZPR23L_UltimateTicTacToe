
#include <sstream>
#include "../../include/entities/InnerBoard.h"
#include <stdexcept>

InnerBoard::InnerBoard(int boardSize) : BoardBase(boardSize){
    playBoard = std::make_unique<std::unique_ptr<char[]>[]>(boardSize);
    for (int i = 0; i < boardSize; i++) {
        playBoard[i] = std::make_unique<char[]>(boardSize);
    }
    FillBoard();
}

void InnerBoard::FillBoard() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            playBoard[i][j] = ' ';
        }
    }
}

void InnerBoard::MakeMove(Point coordinates, char figure) {
    VerifyFigure(figure);
    VerifyCoordinates(coordinates);
    if(playBoard[coordinates.x][coordinates.y] != ' ')
    {
        throw std::invalid_argument("given given cell is already filled");
    }
    playBoard[coordinates.x][coordinates.y] = figure;
}

std::string InnerBoard::ToString() const {
    std::ostringstream stringStream;
    stringStream << " |";
    for (int i = 0; i < boardSize; i++) {
        stringStream << i + 1 << "|";
    }
    stringStream << "\n-+";
    for (int i = 0; i < boardSize; i++) {
        stringStream << "-+";
    }
    stringStream << "\n";
    for (int i = 0; i < boardSize; i++) {
        stringStream << i + 1 << "|";
        for (int j = 0; j < boardSize; j++) {
            stringStream << playBoard[i][j];
            stringStream << "|";
        }
        stringStream << "\n-+";
        for (int j = 0; j < boardSize; j++) {
            stringStream << "-+";
        }
        stringStream << "\n";
    }
    return stringStream.str();
}