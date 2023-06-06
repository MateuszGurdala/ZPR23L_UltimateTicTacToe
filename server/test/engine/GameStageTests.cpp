#include "../../include/gameengine/GameStage.hpp"
#include <memory>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Game stage should use only valid stages and throw if invalid") {
  std::unique_ptr<GameStage> gameStage = std::make_unique<GameStage>();

  SECTION("Valid game stage should be accepted") {
    std::string validGameStage = "Player X Turn";
    REQUIRE_NOTHROW(gameStage->SetGameStage(validGameStage));
    REQUIRE(gameStage->GetCurrentGameStage() == validGameStage);
  }

  SECTION("Invalid game stage should throw an exception") {
    std::string invalidStage = "Player Mati Turn";
    REQUIRE_THROWS_AS(gameStage->SetGameStage(invalidStage), std::invalid_argument);
  }
}
