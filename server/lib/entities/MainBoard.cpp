#include <iostream>
#include <sstream>
#include "../../include/entities/MainBoard.hpp"
#include "../../include/helpers/BoardIndexConverter.hpp"

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
        throw std::invalid_argument("given cell is already filled");
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

std::string MainBoard::WinnerBoardToJson(bool isNested){
    std::stringstream ss;
    if(!isNested)
    {
        ss << "{";
    }
    ss << "\"winnerBoard\":[";
    for (int boardRow = 0; boardRow < boardSize; boardRow++) {
        for (int boardColumn = 0; boardColumn < boardSize; boardColumn++) {
            auto currentPoint = Point(boardRow, boardColumn);
            int id = BoardIndexConverter::PointToIndex(currentPoint, boardSize);
            ss << "{";
            ss << R"("id": ")" << id << R"(",)" ;
            ss << R"("winner": )";
            ss << "\"" << winnerBoard[boardRow][boardColumn] << "\"";
            ss << "}";
            if (boardColumn != boardSize - 1) {
                ss << ",";
            }
        }
        if (boardRow != boardSize - 1) {
            ss << ",";
        }
    }
    ss << "]";
    if(!isNested)
    {
        ss << "}";
    }
    return ss.str();
}

std::string MainBoard::ToJson(bool isNested) {
    std::stringstream ss;
    if(!isNested)
    {
        ss << "{";
    }
    ss << "\"segments\":[";
    for (int boardRow = 0; boardRow < boardSize; boardRow++) {
        for (int boardColumn = 0; boardColumn < boardSize; boardColumn++) {
            ss << "{";
            auto currentPoint = Point(boardRow,boardColumn);
            int id = BoardIndexConverter::PointToIndex(currentPoint, boardSize);
            ss << R"("id": ")" << id << R"(",)";
            ss << R"("winner": )";
            ss << "\"" << winnerBoard[boardRow][boardColumn] << "\",";
            ss << "}";
            if (boardColumn != boardSize - 1) {
                ss << ",";
            }
        }
        if (boardRow != boardSize - 1) {
            ss << ",";
        }
    }
    ss << "]";
    if(!isNested)
    {
        ss << "}";
    }
    return ss.str();
}
