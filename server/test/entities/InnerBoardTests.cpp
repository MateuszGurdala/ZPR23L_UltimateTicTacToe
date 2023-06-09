#include <catch2/catch_all.hpp>

#include "../../include/entities/InnerBoard.hpp"

TEST_CASE("InnerBoard is created and contains only whitespaces after"
          "initialization") {

  unsigned int boardSize = 10;
  std::unique_ptr<InnerBoard> innerBoard =
      std::make_unique<InnerBoard>(boardSize);

  REQUIRE(innerBoard->getBoardSize() == boardSize);

  for (unsigned int i = 0; i < boardSize; i++) {
    for (unsigned int j = 0; j < boardSize; j++) {
      REQUIRE(innerBoard->getCell(Point(i, j)) == ' ');
    }
  }
}

TEST_CASE("InnerBoard is serialized into json.") {

  unsigned int boardSize = 3;
  InnerBoard innerBoard(boardSize);

  Point coordinatesA(0, 0);
  char figureA = 'X';
  innerBoard.placeFigure(coordinatesA, figureA);

  Point coordinatesB(1, 1);
  char figureB = 'O';
  innerBoard.placeFigure(coordinatesB, figureB);

  std::string json = innerBoard.toJson(false);

  std::string expectedJson = R"({
        "segments":[
            {"id": "0", "winner": "X"},
            {"id": "1", "winner": " "},
            {"id": "2", "winner": " "},
            {"id": "3", "winner": " "},
            {"id": "4", "winner": "O"},
            {"id": "5", "winner": " "},
            {"id": "6", "winner": " "},
            {"id": "7", "winner": " "},
            {"id": "8", "winner": " "}
        ]
    })";

  expectedJson.erase(
      std::remove_if(expectedJson.begin(), expectedJson.end(), ::isspace),
      expectedJson.end());
  json.erase(std::remove_if(json.begin(), json.end(), ::isspace), json.end());

  REQUIRE(json == expectedJson);
}

TEST_CASE("placeFigure throws invalid_argument for already filled cell") {
  unsigned int boardSize = 3;
  InnerBoard innerBoard(boardSize);

  Point coordinates(0, 0);
  char figure = 'X';
  innerBoard.placeFigure(coordinates, figure);

  REQUIRE_THROWS_AS(innerBoard.placeFigure(coordinates, figure),
                    std::invalid_argument);
  REQUIRE_THROWS_WITH(innerBoard.placeFigure(coordinates, figure),
                      "given given cell is already filled");
}

TEST_CASE("placeFigure places the figure correctly on the board") {
  unsigned int boardSize = 3;
  InnerBoard innerBoard(boardSize);

  Point coordinates(0, 0);
  char figure = 'X';
  innerBoard.placeFigure(coordinates, figure);

  REQUIRE(innerBoard.getCell(coordinates) == figure);
}