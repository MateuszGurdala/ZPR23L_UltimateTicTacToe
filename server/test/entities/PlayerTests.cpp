#include <catch2/catch_test_macros.hpp>
#include "../../include/entities/ComputerPlayer.hpp"
#include "../../include/entities/HumanPlayer.hpp"

TEST_CASE("Computer Player is constructed") {
    char symbol = 'X';
    ComputerPlayer player(symbol);

    REQUIRE(player.GetSymbol() == symbol);
}

TEST_CASE("Human Player is constructed with correct symbol and name") {
    char symbol = 'X';
    std::string name = "Adam";
    HumanPlayer player(symbol, name);

    REQUIRE(player.GetSymbol() == symbol);
    REQUIRE(player.GetName() == name);

}

TEST_CASE("GetName returns the correct name for computer player") {
    char symbol = 'X';
    std::string correctName = "Computer";
    ComputerPlayer player(symbol);

    REQUIRE(player.GetName() == correctName);
}

TEST_CASE("HumanPlayer name should not exceed 20 characters and contain only letters") {

    SECTION("Name length exceeds 20 characters") {
        REQUIRE_THROWS_AS(HumanPlayer('X', "ThisNameIsTooLongToBeValid"), std::invalid_argument);
    }

    SECTION("Name contains not only letters") {
        REQUIRE_THROWS_AS(HumanPlayer('X', "John123"), std::invalid_argument);
        REQUIRE_THROWS_AS(HumanPlayer('O', "Alice!"), std::invalid_argument);
    }
}