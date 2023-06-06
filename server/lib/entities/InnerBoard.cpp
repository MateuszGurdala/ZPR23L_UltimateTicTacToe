
#include "../../include/entities/InnerBoard.hpp"
#include "../../include/helpers/BoardIndexConverter.hpp"
#include <sstream>
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

void InnerBoard::placeFigure(Point &coordinates, char &figure) {
  verifyFigure(figure);
  verifyCoordinates(coordinates);
  if (playBoard[coordinates.x][coordinates.y] != ' ') {
    throw std::invalid_argument("given given cell is already filled");
  }
  playBoard[coordinates.x][coordinates.y] = figure;
}

std::string InnerBoard::toJson(bool isNested) {
  std::stringstream ss;
  if (!isNested) {
    ss << "{";
  }
  ss << "\"segments\":[";
  for (unsigned int boardRow = 0; boardRow < boardSize; boardRow++) {
    for (unsigned int boardColumn = 0; boardColumn < boardSize; boardColumn++) {
      auto currentPoint = Point(boardRow, boardColumn);
      int id = BoardIndexConverter::pointToIndex(currentPoint, boardSize);
      ss << "{";
      ss << R"("id": ")" << id << R"(",)";
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
  if (!isNested) {
    ss << "}";
  }
  return ss.str();
}

char InnerBoard::getCell(Point coordinates) {
  return playBoard[coordinates.x][coordinates.y];
}

std::vector<char>
InnerBoard::getLeftDiagonalValues(Point &chosenCoordinates) const {
  std::vector<char> diagonalSymbols;
  unsigned int tempX = chosenCoordinates.x;
  unsigned int tempY = chosenCoordinates.y;

  while (tempX > 0 && tempY > 0) {
    --tempX;
    --tempY;
  }
  while (tempX < boardSize && tempY < boardSize) {
    diagonalSymbols.emplace_back(playBoard[tempX][tempY]);
    ++tempX;
    ++tempY;
  }

  return diagonalSymbols;
}

std::vector<char>
InnerBoard::getRightDiagonalValues(Point &chosenCoordinates) const {
  std::vector<char> diagonalSymbols;
  int tempX = (int)chosenCoordinates.x;
  int tempY = (int)chosenCoordinates.y;

  while (tempX < (int)boardSize - 1 && tempY > 0) {
    ++tempX;
    --tempY;
  }

  while (tempX >= 0 && tempY < (int)boardSize) {
    diagonalSymbols.emplace_back(playBoard[tempX][tempY]);
    --tempX;
    ++tempY;
  }

  return diagonalSymbols;
}

std::vector<char>
InnerBoard::getHorizontalValues(Point &chosenCoordinates) const {
  std::vector<char> horizontalSymbols;
  for (unsigned int rowRightIndex = chosenCoordinates.x;
       rowRightIndex < boardSize; rowRightIndex++) {
    horizontalSymbols.emplace_back(
        playBoard[rowRightIndex][chosenCoordinates.y]);
  }
  for (int rowLeftIndex = (int)chosenCoordinates.x - 1; rowLeftIndex >= 0;
       rowLeftIndex--) {
    horizontalSymbols.emplace_back(
        playBoard[rowLeftIndex][chosenCoordinates.y]);
  }
  return horizontalSymbols;
}

std::vector<char>
InnerBoard::getVerticalValues(Point &chosenCoordinates) const {
  std::vector<char> verticalSymbols;
  for (unsigned int columnUpIndex = chosenCoordinates.y;
       columnUpIndex < boardSize; columnUpIndex++) {
    verticalSymbols.emplace_back(playBoard[chosenCoordinates.x][columnUpIndex]);
  }
  for (int columnDownIndex = (int)chosenCoordinates.y - 1; columnDownIndex >= 0;
       columnDownIndex--) {
    verticalSymbols.emplace_back(
        playBoard[chosenCoordinates.x][columnDownIndex]);
  }
  return verticalSymbols;
}
