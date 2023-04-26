#ifndef ULTIMATETICTACTOESERVER_BOARDINDEXCONVERTER_HPP
#define ULTIMATETICTACTOESERVER_BOARDINDEXCONVERTER_HPP

#include "../entities/BoardBase.hpp"

class BoardIndexConverter {
public:
    static int PointToIndex(Point& point, int& boardSize);
    static Point IndexToPoint(int& index, int& boardSize);
};

#endif //ULTIMATETICTACTOESERVER_BOARDINDEXCONVERTER_HPP
