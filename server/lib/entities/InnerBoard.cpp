
#include <sstream>
#include "../../include/entities/InnerBoard.hpp"
#include "../../include/helpers/BoardIndexConverter.hpp"
#include <stdexcept>

InnerBoard::InnerBoard(unsigned int boardSize) : BoardBase(boardSize) {
    playBoard.resize(boardSize);
    for (unsigned int i = 0; i < boardSize; i++) {
        playBoard[i].resize(boardSize);
    }
    FillBoard();
}

void InnerBoard::FillBoard() {
    for (unsigned int i = 0; i < boardSize; i++) {
        for (unsigned int j = 0; j < boardSize; j++) {
            playBoard[i][j] = ' ';
        }
    }
}

void InnerBoard::PlaceFigure(Point& coordinates, char& figure) {
    VerifyFigure(figure);
    VerifyCoordinates(coordinates);
    if(playBoard[coordinates.x][coordinates.y] != ' ')
    {
        throw std::invalid_argument("given given cell is already filled");
    }
    playBoard[coordinates.x][coordinates.y] = figure;
}

std::string InnerBoard::ToJson(bool isNested) {
    std::stringstream ss;
    if(!isNested)
    {
        ss << "{";
    }
    ss << "\"segments\":[";
    for (unsigned int boardRow = 0; boardRow < boardSize; boardRow++) {
        for (unsigned int boardColumn = 0; boardColumn < boardSize; boardColumn++) {
            auto currentPoint = Point(boardRow, boardColumn);
            int id = BoardIndexConverter::PointToIndex(currentPoint, boardSize);
            ss << "{";
            ss << R"("id": ")" << id << R"(",)" ;
            ss << R"("winner": )";
            ss << "\"" << playBoard[boardRow][boardColumn] << "\"";
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

char InnerBoard::GetCell(Point coordinates) {
    return playBoard[coordinates.x][coordinates.y];
}

const std::vector<std::vector<char>>& InnerBoard::GetPlayBoard() const {
    return playBoard;
}