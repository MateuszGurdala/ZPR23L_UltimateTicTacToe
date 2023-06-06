#include "../../include/helpers/BoardIndexConverter.hpp"
#include "../../include/helpers/MoveSimulator.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("PointToIndex converts point to index correctly") {
  unsigned int boardSize = 3;

  Point point1(0, 0);
  unsigned int index1 = BoardIndexConverter::PointToIndex(point1, boardSize);
  REQUIRE(index1 == 0);

  Point point2(1, 2);
  unsigned int index2 = BoardIndexConverter::PointToIndex(point2, boardSize);
  REQUIRE(index2 == 5);

  Point point3(2, 1);
  unsigned int index3 = BoardIndexConverter::PointToIndex(point3, boardSize);
  REQUIRE(index3 == 7);
}

TEST_CASE("IndexToPoint converts index to point correctly") {
  unsigned int boardSize = 3;

  unsigned int index1 = 0;
  Point point1 = BoardIndexConverter::IndexToPoint(index1, boardSize);
  REQUIRE(point1.x == 0);
  REQUIRE(point1.y == 0);

  unsigned int index2 = 5;
  Point point2 = BoardIndexConverter::IndexToPoint(index2, boardSize);
  REQUIRE(point2.x == 1);
  REQUIRE(point2.y == 2);

  unsigned int index3 = 7;
  Point point3 = BoardIndexConverter::IndexToPoint(index3, boardSize);
  REQUIRE(point3.x == 2);
  REQUIRE(point3.y == 1);
}

TEST_CASE("Move Simulator performs valid random move") {
  std::vector<std::vector<Point>> movesToChooseFrom = {
      {Point(0, 0), Point(0, 1)},
      {Point(0, 2), Point(2, 1)},
      {Point(1, 2)},
      {},
      {},
      {},
      {},
      {},
      {}};
  unsigned int boardSize = 3;

  SECTION("Segment is not chosen, any vector is available") {
    int chosenSegment = -1;

    std::array<Point, 2> result = MoveSimulator::PerformRandomMove(
        movesToChooseFrom, boardSize, chosenSegment);

    REQUIRE(result.size() == 2);

    Point outerPoint = result[0];
    Point chosenPoint = result[1];

    REQUIRE(outerPoint.x < boardSize);
    REQUIRE(outerPoint.y < boardSize);
    REQUIRE(chosenPoint.x < boardSize);
    REQUIRE(chosenPoint.y < boardSize);
  }
  SECTION("Segment is chosen, only one point inside this segment"
          " is available") {
    int chosenSegment = 2;

    std::array<Point, 2> result = MoveSimulator::PerformRandomMove(
        movesToChooseFrom, boardSize, chosenSegment);

    REQUIRE(result.size() == 2);

    Point outerBoardPoint = result[0];
    Point chosenPoint = result[1];

    REQUIRE(outerBoardPoint.x == 0);
    REQUIRE(outerBoardPoint.y == 2);
    REQUIRE(chosenPoint.x == 1);
    REQUIRE(chosenPoint.y == 2);
  }
}