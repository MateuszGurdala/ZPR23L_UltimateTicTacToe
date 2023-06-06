
#include "../../include/gameengine/GameEngine.hpp"
#include "../../include/helpers/BoardIndexConverter.hpp"
#include "../../include/helpers/MoveSimulator.hpp"
#include <algorithm>
#include <memory>

GameEngine::GameEngine(std::unique_ptr<MainBoard> mainBoard)
    : mainBoard(std::move(mainBoard)) {
  allAvailableBoardMoves = initializeAvailableInnerBoardMoves();
  currentLegalMoves = allAvailableBoardMoves;
  currentSegment = -1;
}

std::vector<Point> GameEngine::initializeAvailableSingleBoardMoves() {
  unsigned int boardSize = getBoardSize();
  std::vector<Point> availableMoves;
  availableMoves.reserve(boardSize * boardSize);
  for (unsigned int x = 0; x < boardSize; x++) {
    for (unsigned int y = 0; y < boardSize; y++) {
      availableMoves.emplace_back(x, y);
    }
  }
  return availableMoves;
}

std::vector<std::vector<Point>>
GameEngine::initializeAvailableInnerBoardMoves() {
  unsigned int boardSize = getBoardSize();
  std::vector<std::vector<Point>> availableMoves;
  availableMoves.reserve(boardSize * boardSize);
  for (unsigned int n = 0; n < boardSize * boardSize; n++) {
    availableMoves.emplace_back(initializeAvailableSingleBoardMoves());
  }
  return availableMoves;
}

bool GameEngine::isSegmentChosen(Point &innerBoardCoordinates) {
  unsigned int boardSize = getBoardSize();
  currentSegment =
      BoardIndexConverter::pointToIndex(innerBoardCoordinates, boardSize);
  if (mainBoard->getWinnerBoardCell(innerBoardCoordinates) != ' ' ||
      allAvailableBoardMoves[currentSegment].empty()) {
    return false;
  }
  return true;
}
std::array<Point, 2> GameEngine::handleComputerMove() {
  return MoveSimulator::performRandomMove(currentLegalMoves, getBoardSize(),
                                          currentSegment);
}

void GameEngine::updateCurrentLegalMoves(Point &innerBoardCoordinates) {
  currentLegalMoves.clear();
  unsigned int boardSize = getBoardSize();
  currentLegalMoves.resize(boardSize * boardSize);
  if (!isSegmentChosen(innerBoardCoordinates)) {
    currentSegment = -1;
    for (unsigned int i = 0; i < allAvailableBoardMoves.size(); i++) {
      for (const auto &point : allAvailableBoardMoves[i]) {
        currentLegalMoves[i].emplace_back(point);
      }
    }
    return;
  }
  currentSegment =
      BoardIndexConverter::pointToIndex(innerBoardCoordinates, boardSize);
  unsigned int outerBoardIndex =
      BoardIndexConverter::pointToIndex(innerBoardCoordinates, boardSize);
  currentLegalMoves[outerBoardIndex] = allAvailableBoardMoves[outerBoardIndex];
}

void GameEngine::handleMove(Point &boardCoordinates, Point &innerCoordinates,
                            char figure) {
  mainBoard->makeMove(boardCoordinates, innerCoordinates, figure);
  unsigned int boardSize = getBoardSize();
  unsigned int innerBoardIndex =
      BoardIndexConverter::pointToIndex(boardCoordinates, boardSize);
  removePointFromAllAvailableMoves(innerBoardIndex, innerCoordinates);
}

bool GameEngine::checkForLocalWinner(Point &mainBoardCoordinates,
                                     Point &innerBoardCellCoordinates,
                                     char figure) {
  auto &innerBoard = mainBoard->getInnerBoard(mainBoardCoordinates);
  unsigned int boardSize = getBoardSize();
  unsigned int mainBoardIndex =
      BoardIndexConverter::pointToIndex(mainBoardCoordinates, boardSize);
  auto figuresInPattern =
      innerBoard.getHorizontalValues(innerBoardCellCoordinates);
  if (areAllValuesTheSame(figuresInPattern)) {
    mainBoard->addWinnerOfInnerBoard(mainBoardCoordinates, figure);
    allAvailableBoardMoves[mainBoardIndex].clear();
    return true;
  }
  figuresInPattern = innerBoard.getVerticalValues(innerBoardCellCoordinates);
  if (areAllValuesTheSame(figuresInPattern)) {
    mainBoard->addWinnerOfInnerBoard(mainBoardCoordinates, figure);
    allAvailableBoardMoves[mainBoardIndex].clear();
    return true;
  }
  figuresInPattern =
      innerBoard.getLeftDiagonalValues(innerBoardCellCoordinates);
  if (figuresInPattern.size() == mainBoard->getBoardSize() &&
      areAllValuesTheSame(figuresInPattern)) {
    mainBoard->addWinnerOfInnerBoard(mainBoardCoordinates, figure);
    allAvailableBoardMoves[mainBoardIndex].clear();
    return true;
  }
  figuresInPattern =
      innerBoard.getRightDiagonalValues(innerBoardCellCoordinates);
  if (figuresInPattern.size() == mainBoard->getBoardSize() &&
      areAllValuesTheSame(figuresInPattern)) {
    mainBoard->addWinnerOfInnerBoard(mainBoardCoordinates, figure);
    allAvailableBoardMoves[mainBoardIndex].clear();
    return true;
  }
  return false;
}
bool GameEngine::checkIfAnyMovesLeft() {
  unsigned int boardSize = getBoardSize();
  for (unsigned int i = 0; i < allAvailableBoardMoves.size(); i++) {
    if (!allAvailableBoardMoves[i].empty()) {
      return true;
    }
    Point boardIndex = BoardIndexConverter::indexToPoint(i, boardSize);
    if (mainBoard->getWinnerBoardCell(boardIndex) == ' ') {
      return true;
    }
  }

  return false;
}

bool GameEngine::checkForGlobalWinner(
    Point &changedWinnerBoardCellCoordinates) {
  auto figuresInPattern = mainBoard->getWinnerBoard().getHorizontalValues(
      changedWinnerBoardCellCoordinates);
  if (areAllValuesTheSame(figuresInPattern)) {
    return true;
  }
  figuresInPattern = mainBoard->getWinnerBoard().getVerticalValues(
      changedWinnerBoardCellCoordinates);
  if (areAllValuesTheSame(figuresInPattern)) {
    return true;
  }
  figuresInPattern = mainBoard->getWinnerBoard().getLeftDiagonalValues(
      changedWinnerBoardCellCoordinates);
  if (figuresInPattern.size() == mainBoard->getBoardSize() &&
      areAllValuesTheSame(figuresInPattern)) {
    return true;
  }
  figuresInPattern = mainBoard->getWinnerBoard().getRightDiagonalValues(
      changedWinnerBoardCellCoordinates);
  if (figuresInPattern.size() == mainBoard->getBoardSize() &&
      areAllValuesTheSame(figuresInPattern)) {
    return true;
  }
  return false;
}

bool GameEngine::areAllValuesTheSame(const std::vector<char> &values) {
  auto it =
      std::adjacent_find(values.begin(), values.end(), std::not_equal_to<>());
  if (it != values.end()) {
    return false;
  }

  bool containsWhitespace =
      std::any_of(values.begin(), values.end(),
                  [](char value) { return std::isspace(value); });

  return !containsWhitespace;
}

std::vector<std::vector<Point>> &GameEngine::getAvailableInnerBoardMoves() {
  return allAvailableBoardMoves;
}

unsigned int GameEngine::getBoardSize() { return mainBoard->getBoardSize(); }
int GameEngine::getCurrentSegment() const { return currentSegment; }

std::string GameEngine::getWinnerBoardAsJson(bool isNested) {
  return mainBoard->winnerBoardToJson(isNested);
}

void GameEngine::removePointFromAllAvailableMoves(
    unsigned int innerBoardIndex, Point &pointOfInnerBoardToRemove) {
  auto &innerBoard = allAvailableBoardMoves[innerBoardIndex];
  unsigned int x = pointOfInnerBoardToRemove.x;
  unsigned int y = pointOfInnerBoardToRemove.y;
  innerBoard.erase(std::remove_if(innerBoard.begin(), innerBoard.end(),
                                  [x, y](const Point &point) {
                                    return (point.x == x && point.y == y);
                                  }),
                   innerBoard.end());
}

std::string GameEngine::getBoardAsJson(bool isNested) {
  return mainBoard->toJson(isNested);
}
