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

