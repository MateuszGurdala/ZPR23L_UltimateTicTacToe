#include <catch2/catch_test_macros.hpp>
#include "../../include/helpers/BoardIndexConverter.hpp"


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