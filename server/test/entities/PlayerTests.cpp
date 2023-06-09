#include "../../include/entities/ComputerPlayer.hpp"
#include "../../include/entities/HumanPlayer.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Computer Player is constructed") {
  char symbol = 'X';
  std::unique_ptr<ComputerPlayer> player =
      std::make_unique<ComputerPlayer>(symbol);

  REQUIRE(player->getSymbol() == symbol);
}

TEST_CASE("Human Player is constructed with correct symbol and name") {
  char symbol = 'X';
  std::string name = "Adam";
  std::unique_ptr<HumanPlayer> player =
      std::make_unique<HumanPlayer>(symbol, name);

  REQUIRE(player->getSymbol() == symbol);
  REQUIRE(player->getName() == name);
}

TEST_CASE("getName returns the correct name for computer player") {
  char symbol = 'X';
  std::string correctName = "Computer";
  ComputerPlayer player(symbol);

  REQUIRE(player.getName() == correctName);
}

TEST_CASE("HumanPlayer name should not exceed 20 characters and contain only "
          "letters") {

  SECTION("Name length exceeds 20 characters") {
    REQUIRE_THROWS_AS(HumanPlayer('X', "ThisNameIsTooLongToBeValid"),
                      std::invalid_argument);
  }

  SECTION("Name contains not only letters") {
    REQUIRE_THROWS_AS(HumanPlayer('X', "John123"), std::invalid_argument);
    REQUIRE_THROWS_AS(HumanPlayer('O', "Alice!"), std::invalid_argument);
  }
}