#include <catch2/catch_test_macros.hpp>
#include "../../include/entities/MainBoard.hpp"

TEST_CASE("MainBoard constructor initializes mainPlayBoard and winnerBoard correctly") {
    unsigned int boardSize = 3;
    MainBoard mainBoard(boardSize);

    SECTION("mainPlayBoard is initialized correctly") {
        REQUIRE(mainBoard.GetBoardSize() == boardSize);

        for (unsigned int i = 0; i < boardSize; i++) {
            for (unsigned int j = 0; j < boardSize; j++) {
                REQUIRE(mainBoard.GetInnerBoard(Point(i,j)) != nullptr);
                REQUIRE(mainBoard.GetInnerBoard(Point(i,j))->GetBoardSize() == boardSize);
            }
        }
    }

    SECTION("winnerBoard is initialized correctly") {

        for (unsigned int i = 0; i < boardSize; i++) {
            for (unsigned int j = 0; j < boardSize; j++) {
                REQUIRE(mainBoard.GetWinnerBoardCell(Point(i,j)) == ' ');
            }
        }
    }
}