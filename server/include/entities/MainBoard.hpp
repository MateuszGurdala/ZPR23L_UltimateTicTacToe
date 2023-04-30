#ifndef ULTIMATETICTACTOESERVER_MAINBOARD_HPP
#define ULTIMATETICTACTOESERVER_MAINBOARD_HPP

#include "InnerBoard.hpp"
#include <vector>

/*  Class: MainBoard
        Outer board of the game which includes 2d vector of InnerBoards. Also has helper array
        called winnerBoard which stores information who won specific inner board.

        see also:
        <InnerBoard>
 */
class MainBoard : public BoardBase {
private:
    std::vector<std::vector<std::unique_ptr<InnerBoard>>> mainPlayBoard;
    std::unique_ptr<std::unique_ptr<char[]>[]> winnerBoard;
    /*  Function: FillBoard
    Fills main play board with InnerBoard objects and winner board with whitespaces.
     */
    void FillBoard() override;
public:
    /*  Constructor: MainBoard
    Constructor which takes size of board as parameter. Initializes winner board and main play board
    */
    MainBoard(int boardSize);
    void Print() const;
    void AddWinnerOfInnerBoard(Point& coordinates, char& figure);
    void MakeMove(Point& boardCoordinates, Point& innerCoordinates, char figure);
    //TODO to be implemented
    auto GetInnerBoardVerticalValues(Point& playBoardCoordinates, Point& innerBoardRowAndColumn);
    auto GetInnerBoarHorizontalValues(Point& playBoardCoordinates, Point& innerBoardRowAndColumn);
    auto GetInnerBoardLeftDiagonalValues(Point& playBoardCoordinates, Point& innerBoardRowAndColumn);
    auto GetInnerBoardRightDiagonalValues(Point& playBoardCoordinates, Point& innerBoardRowAndColumn);
    /*  Function: ToJson

     */
    std::string ToJson(bool isNested) override;
    /*  Function: WinnerBoardToJson

    */
    std::string WinnerBoardToJson(bool isNested);
};

#endif //ULTIMATETICTACTOESERVER_MAINBOARD_HPP
