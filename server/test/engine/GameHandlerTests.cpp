#include "../../include/gameengine/GameHandler.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("GameHandler constructor works and game starts correctly"
          "with X player starting") {

  unsigned int boardSize = 3;
  char hostSymbol = 'X';
  bool isPlayerVsComputer = false;
  std::string hostName = "Krystian";
  std::string guestName = "Mati";

  std::unique_ptr<GameHandler> gameHandler = std::make_unique<GameHandler>(
      boardSize, hostSymbol, isPlayerVsComputer, hostName, guestName);

  REQUIRE(gameHandler->GetGameStage() == "Player X Turn, choose segment");
  REQUIRE(gameHandler->GetSegmentIndex() == -1);
}
TEST_CASE(
    "Verify if Game is against computer and computer starts, current symbol"
    "should be host symbol and segment is chosen") {
  unsigned int boardSize = 5;
  char hostSymbol = 'O';
  bool isPlayerVsComputer = true;
  std::string hostName = "Krystian";

  std::unique_ptr<GameHandler> gameHandler = std::make_unique<GameHandler>(
      boardSize, hostSymbol, isPlayerVsComputer, hostName);
  REQUIRE(gameHandler->GetGameStage() == "Player O Turn");
  REQUIRE(gameHandler->GetSegmentIndex() != -1);
}

TEST_CASE("After move is made in game versus second human player"
          "the current turn is the O turn. Also test move validation") {
  unsigned int boardSize = 5;
  char hostSymbol = 'X';
  bool isPlayerVsComputer = false;
  std::string hostName = "Krystian";
  std::string guestName = "Mati";

  std::unique_ptr<GameHandler> gameHandler = std::make_unique<GameHandler>(
      boardSize, hostSymbol, isPlayerVsComputer, hostName, guestName);
  Point outerBoardPoint = Point(0, 0);
  Point innerBoardPoint = Point(0, 0);
  Point invalidInnerBoardPoint = Point(-1, -1);
  SECTION("Move validation if performed") {
    bool isValidMove =
        gameHandler->PerformMoveValidation(outerBoardPoint, innerBoardPoint);
    REQUIRE(isValidMove == true);
  }
  SECTION("Move validation if performed. Case with negative coordinates") {
    bool isValidMove = gameHandler->PerformMoveValidation(
        outerBoardPoint, invalidInnerBoardPoint);
    REQUIRE(isValidMove == false);
  }
  gameHandler->PerformTurn(outerBoardPoint, innerBoardPoint);
  REQUIRE(gameHandler->GetGameStage() == "Player O Turn");
  REQUIRE(gameHandler->GetSegmentIndex() == 0);
}