#include "../../include/gameengine/GameEngine.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Check if game engine and all available moves are correctly "
          "initialized") {
  unsigned int boardSize = 3;
  std::unique_ptr<MainBoard> mainBoard = std::make_unique<MainBoard>(boardSize);
  std::unique_ptr<GameEngine> gameEngine =
      std::make_unique<GameEngine>(std::move(mainBoard));


  REQUIRE(gameEngine->GetAvailableInnerBoardMoves().size() == boardSize * boardSize);
  for (const auto& moves : gameEngine->GetAvailableInnerBoardMoves()) {
    REQUIRE(moves.size() == boardSize * boardSize);
  }
}