//TODO implement advanced AI


#include "../../include/entities/ComputerPlayer.hpp"
#include "../../include/helpers/BoardIndexConverter.hpp"


std::array<Point, 2> ComputerPlayer::ChooseMove(const std::vector<Point>& availableOuterBoardMoves,
                                                std::vector<std::vector<Point>> availableInnerBoardMoves, int boardSize){
    std::array<Point, 2> playerMove{};
    auto& outerBoardCoords = SimulateMove(availableOuterBoardMoves);
    int innerIndex = BoardIndexConverter::PointToIndex(outerBoardCoords, boardSize);
    auto& innerBoardCoords = SimulateMove(availableInnerBoardMoves[innerIndex]);
    playerMove[0] = outerBoardCoords;
    playerMove[1] = innerBoardCoords;
    return playerMove;
}

//TODO change/remove after implementing MINMAX
Point& ComputerPlayer::SimulateMove(const std::vector<Point>& availableMoves) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, availableMoves.size() - 1);
    int index = dis(gen);

    auto& move = const_cast<Point&>(availableMoves[index]);
    return move;
}

ComputerPlayer::ComputerPlayer(char symbol) : Player(symbol) {
    name = "Computer";
}