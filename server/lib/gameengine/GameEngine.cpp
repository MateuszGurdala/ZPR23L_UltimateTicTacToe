
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
  unsigned int boardSize = GetBoardSize();
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
  unsigned int boardSize = GetBoardSize();
  std::vector<std::vector<Point>> availableMoves;
  availableMoves.reserve(boardSize * boardSize);
  for (unsigned int n = 0; n < boardSize * boardSize; n++) {
    availableMoves.emplace_back(initializeAvailableSingleBoardMoves());
  }
  return availableMoves;
}

bool GameEngine::IsSegmentChoosen(Point &innerBoardCoordinates) {
  unsigned int boardSize = GetBoardSize();
  currentSegment =
      BoardIndexConverter::PointToIndex(innerBoardCoordinates, boardSize);
  if (mainBoard->GetWinnerBoardCell(innerBoardCoordinates) != ' ' ||
      allAvailableBoardMoves[currentSegment].empty()) {
    return false;
  }
  return true;
}
std::array<Point, 2> GameEngine::HandleComputerMove() {
  return MoveSimulator::PerformRandomMove(currentLegalMoves, GetBoardSize(),
                                          currentSegment);
}

void GameEngine::UpdateCurrentLegalMoves(Point &innerBoardCoordinates) {
  currentLegalMoves.clear();
  unsigned int boardSize = GetBoardSize();
  currentLegalMoves.resize(boardSize * boardSize);
  if (!IsSegmentChoosen(innerBoardCoordinates)) {
    currentSegment = -1;
    for (unsigned int i = 0; i < allAvailableBoardMoves.size(); i++) {
      for (const auto &point : allAvailableBoardMoves[i]) {
        currentLegalMoves[i].emplace_back(point);
      }
    }
    return;
  }
  currentSegment =
      BoardIndexConverter::PointToIndex(innerBoardCoordinates, boardSize);
  unsigned int outerBoardIndex =
      BoardIndexConverter::PointToIndex(innerBoardCoordinates, boardSize);
  currentLegalMoves[outerBoardIndex] = allAvailableBoardMoves[outerBoardIndex];
}

void GameEngine::HandleMove(Point &boardCoordinates, Point &innerCoordinates,
                            char figure) {
  mainBoard->MakeMove(boardCoordinates, innerCoordinates, figure);
  unsigned int boardSize = GetBoardSize();
  unsigned int innerBoardIndex =
      BoardIndexConverter::PointToIndex(boardCoordinates, boardSize);
  RemovePointFromAllAvailableMoves(innerBoardIndex, innerCoordinates);
}

bool GameEngine::CheckForLocalWinner(Point &mainBoardCoordinates,
                                     Point &innerBoardCellCoordinates,
                                     char figure) {
  auto &innerBoard = mainBoard->GetInnerBoard(mainBoardCoordinates);
  unsigned int boardSize = GetBoardSize();
  unsigned int mainBoardIndex =
      BoardIndexConverter::PointToIndex(mainBoardCoordinates, boardSize);
  auto figuresInPattern =
      innerBoard.GetHorizontalValues(innerBoardCellCoordinates);
  if (areAllValuesTheSame(figuresInPattern)) {
    mainBoard->AddWinnerOfInnerBoard(mainBoardCoordinates, figure);
    allAvailableBoardMoves[mainBoardIndex].clear();
    return true;
  }
  figuresInPattern = innerBoard.GetVerticalValues(innerBoardCellCoordinates);
  if (areAllValuesTheSame(figuresInPattern)) {
    mainBoard->AddWinnerOfInnerBoard(mainBoardCoordinates, figure);
    allAvailableBoardMoves[mainBoardIndex].clear();
    return true;
  }
  figuresInPattern =
      innerBoard.GetLeftDiagonalValues(innerBoardCellCoordinates);
  if (figuresInPattern.size() == mainBoard->GetBoardSize() &&
      areAllValuesTheSame(figuresInPattern)) {
    mainBoard->AddWinnerOfInnerBoard(mainBoardCoordinates, figure);
    allAvailableBoardMoves[mainBoardIndex].clear();
    return true;
  }
  figuresInPattern =
      innerBoard.GetRightDiagonalValues(innerBoardCellCoordinates);
  if (figuresInPattern.size() == mainBoard->GetBoardSize() &&
      areAllValuesTheSame(figuresInPattern)) {
    mainBoard->AddWinnerOfInnerBoard(mainBoardCoordinates, figure);
    allAvailableBoardMoves[mainBoardIndex].clear();
    return true;
  }
  return false;
}
bool GameEngine::CheckIfAnyMovesLeft() {
  unsigned int boardSize = GetBoardSize();
  for (unsigned int i = 0; i < allAvailableBoardMoves.size(); i++) {
    if (!allAvailableBoardMoves[i].empty()) {
      return true;
    }
    Point boardIndex = BoardIndexConverter::IndexToPoint(i, boardSize);
    if (mainBoard->GetWinnerBoardCell(boardIndex) == ' ') {
      return true;
    }
  }

  return false;
}

bool GameEngine::CheckForGlobalWinner(
    Point &changedWinnerBoardCellCoordinates) {
  auto figuresInPattern = mainBoard->GetWinnerBoard().GetHorizontalValues(
      changedWinnerBoardCellCoordinates);
  if (areAllValuesTheSame(figuresInPattern)) {
    return true;
  }
  figuresInPattern = mainBoard->GetWinnerBoard().GetVerticalValues(
      changedWinnerBoardCellCoordinates);
  if (areAllValuesTheSame(figuresInPattern)) {
    return true;
  }
  figuresInPattern = mainBoard->GetWinnerBoard().GetLeftDiagonalValues(
      changedWinnerBoardCellCoordinates);
  if (figuresInPattern.size() == mainBoard->GetBoardSize() &&
      areAllValuesTheSame(figuresInPattern)) {
    return true;
  }
  figuresInPattern = mainBoard->GetWinnerBoard().GetRightDiagonalValues(
      changedWinnerBoardCellCoordinates);
  if (figuresInPattern.size() == mainBoard->GetBoardSize() &&
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

std::vector<std::vector<Point>> &GameEngine::GetAvailableInnerBoardMoves() {
  return allAvailableBoardMoves;
}

unsigned int GameEngine::GetBoardSize() { return mainBoard->GetBoardSize(); }
int GameEngine::GetCurrentSegment() const { return currentSegment; }

std::string GameEngine::GetWinnerBoardAsJson(bool isNested) {
  return mainBoard->WinnerBoardToJson(isNested);
}

void GameEngine::RemovePointFromAllAvailableMoves(
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

std::string GameEngine::GetBoardAsJson(bool isNested) {
  return mainBoard->ToJson(isNested);
}
