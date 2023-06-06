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

const InnerBoard &MainBoard::GetInnerBoard(Point point) const {
  return *mainPlayBoard[point.x][point.y];
}

char MainBoard::GetWinnerBoardCell(Point point) {
  return winnerBoard->GetCell(point);
}
const InnerBoard &MainBoard::GetWinnerBoard() const { return *winnerBoard; }

void MainBoard::FillBoard() {
  for (auto &row : mainPlayBoard) {
    for (unsigned int j = 0; j < boardSize; j++) {
      row[j] = std::make_unique<InnerBoard>(boardSize);
    }
  }
}

void MainBoard::AddWinnerOfInnerBoard(Point &coordinates, char &figure) {
  winnerBoard->PlaceFigure(coordinates, figure);
}

void MainBoard::MakeMove(Point &boardCoordinates, Point &innerCoordinates,
                         char figure) {
  mainPlayBoard[boardCoordinates.x][boardCoordinates.y]->PlaceFigure(
      innerCoordinates, figure);
}

std::string MainBoard::WinnerBoardToJson(bool isNested) {
  std::stringstream ss;
  if (!isNested) {
    ss << "{";
  }
  ss << "\"winnerBoard\":[";
  for (unsigned int boardRow = 0; boardRow < boardSize; boardRow++) {
    for (unsigned int boardColumn = 0; boardColumn < boardSize; boardColumn++) {
      auto currentPoint = Point(boardRow, boardColumn);
      int id = BoardIndexConverter::PointToIndex(currentPoint, boardSize);
      ss << "{";
      ss << R"("id": ")" << id << R"(",)";
      ss << R"("winner": )";
      ss << "\"" << winnerBoard->GetCell(currentPoint) << "\"";
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

std::string MainBoard::ToJson(bool isNested) {
  std::stringstream ss;
  if (!isNested) {
    ss << "{";
  }
  ss << "\"segments\":[";
  for (unsigned int boardRow = 0; boardRow < boardSize; boardRow++) {
    for (unsigned int boardColumn = 0; boardColumn < boardSize; boardColumn++) {
      ss << "{";
      auto currentPoint = Point(boardRow, boardColumn);
      int id = BoardIndexConverter::PointToIndex(currentPoint, boardSize);
      ss << R"("id": ")" << id << R"(",)";
      ss << R"("winner": )";
      ss << "\"" << winnerBoard->GetCell(currentPoint) << "\",";
      ss << mainPlayBoard[boardRow][boardColumn]->ToJson(true);
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
