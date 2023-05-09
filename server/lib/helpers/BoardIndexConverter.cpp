#include "../../include/helpers/BoardIndexConverter.hpp"

int BoardIndexConverter::PointToIndex(Point &point, int &boardSize) {
    return point.x * boardSize + point.y;
}

Point BoardIndexConverter::IndexToPoint(int& index, int &boardSize) {
    int y = index % boardSize;
    int x = (index - y)/boardSize;
    auto point = Point(x,y);
    return point;
}
