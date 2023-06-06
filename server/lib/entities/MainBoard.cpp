#include "../../include/entities/MainBoard.hpp"
#include "../../include/helpers/BoardIndexConverter.hpp"
#include <iostream>
#include <sstream>

MainBoard::MainBoard(unsigned int boardSize)
    : BoardBase(boardSize),
      winnerBoard(std::make_unique<InnerBoard>(boardSize)) {

  mainPlayBoard.resize(boardSize);
  for (auto &row : mainPlayBoard) {
    row.resize(boardSize);
  }
  FillBoard();
}

const InnerBoard &MainBoard::getInnerBoard(Point point) const {
  return *mainPlayBoard[point.x][point.y];
}

char MainBoard::getWinnerBoardCell(Point point) {
  return winnerBoard->getCell(point);
}
const InnerBoard &MainBoard::getWinnerBoard() const { return *winnerBoard; }

void MainBoard::FillBoard() {
  for (auto &row : mainPlayBoard) {
    for (unsigned int j = 0; j < boardSize; j++) {
      row[j] = std::make_unique<InnerBoard>(boardSize);
    }
  }
}

void MainBoard::addWinnerOfInnerBoard(Point &coordinates, char &figure) {
  winnerBoard->placeFigure(coordinates, figure);
}

void MainBoard::makeMove(Point &boardCoordinates, Point &innerCoordinates,
                         char figure) {
  mainPlayBoard[boardCoordinates.x][boardCoordinates.y]->placeFigure(
      innerCoordinates, figure);
}

std::string MainBoard::winnerBoardToJson(bool isNested) {
  std::stringstream ss;
  if (!isNested) {
    ss << "{";
  }
  ss << "\"winnerBoard\":[";
  for (unsigned int boardRow = 0; boardRow < boardSize; boardRow++) {
    for (unsigned int boardColumn = 0; boardColumn < boardSize; boardColumn++) {
      auto currentPoint = Point(boardRow, boardColumn);
      int id = BoardIndexConverter::pointToIndex(currentPoint, boardSize);
      ss << "{";
      ss << R"("id": ")" << id << R"(",)";
      ss << R"("winner": )";
      ss << "\"" << winnerBoard->getCell(currentPoint) << "\"";
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
  if (!isNested) {
    ss << "}";
  }
  return ss.str();
}

std::string MainBoard::toJson(bool isNested) {
  std::stringstream ss;
  if (!isNested) {
    ss << "{";
  }
  ss << "\"segments\":[";
  for (unsigned int boardRow = 0; boardRow < boardSize; boardRow++) {
    for (unsigned int boardColumn = 0; boardColumn < boardSize; boardColumn++) {
      ss << "{";
      auto currentPoint = Point(boardRow, boardColumn);
      int id = BoardIndexConverter::pointToIndex(currentPoint, boardSize);
      ss << R"("id": ")" << id << R"(",)";
      ss << R"("winner": )";
      ss << "\"" << winnerBoard->getCell(currentPoint) << "\",";
      ss << mainPlayBoard[boardRow][boardColumn]->toJson(true);
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
  if (!isNested) {
    ss << "}";
  }
  return ss.str();
}
