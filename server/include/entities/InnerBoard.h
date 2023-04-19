#ifndef ULTIMATETICTACTOESERVER_INNERBOARD_H
#define ULTIMATETICTACTOESERVER_INNERBOARD_H

#include <vector>
#include <array>
#include <memory>
#include "BoardBase.h"

class InnerBoard : public BoardBase{
private:
    std::unique_ptr<std::unique_ptr<char[]>[]> playBoard;
    void FillBoard() override;
public:
    InnerBoard(int boardSize);
    std::string ToString() const;

};

#endif //ULTIMATETICTACTOESERVER_INNERBOARD_H
