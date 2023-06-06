#include "../../include/entities/MainBoard.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("MainBoard constructor initializes mainPlayBoard and winnerBoard "
          "correctly") {
  unsigned int boardSize = 3;
  std::unique_ptr<MainBoard> mainBoard = std::make_unique<MainBoard>(boardSize);

  SECTION("mainPlayBoard is initialized correctly with correct sizes") {
    REQUIRE(mainBoard->getBoardSize() == boardSize);

    for (unsigned int i = 0; i < boardSize; i++) {
      for (unsigned int j = 0; j < boardSize; j++) {
        REQUIRE(mainBoard->getInnerBoard(Point(i, j)).getBoardSize() ==
                boardSize);
      }
    }
  }

  SECTION("winnerBoard is initialized correctly") {

    for (unsigned int i = 0; i < boardSize; i++) {
      for (unsigned int j = 0; j < boardSize; j++) {
        REQUIRE(mainBoard->getWinnerBoardCell(Point(i, j)) == ' ');
      }
    }
  }
}