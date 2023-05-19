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
    InnerBoard winnerBoard;
    /*  Function: FillBoard
    Fills main play board with InnerBoard objects and winner board with whitespaces.
     */
    void FillBoard() override;
public:
    /*  Constructor: MainBoard
    Constructor which takes size of board as parameter. Initializes winner board and main play board
    */
    MainBoard(unsigned int boardSize);
    void AddWinnerOfInnerBoard(Point& coordinates, char& figure);
    void MakeMove(Point& boardCoordinates, Point& innerCoordinates, char figure);
    /*  Function: ToJson

     */
    std::string ToJson(bool isNested) override;
    /*  Function: WinnerBoardToJson

    */
    std::string WinnerBoardToJson(bool isNested);

    std::unique_ptr<InnerBoard>& GetInnerBoard(Point point);

    char GetWinnerBoardCell(Point point);
    const InnerBoard& GetWinnerBoard() const;
};

#endif //ULTIMATETICTACTOESERVER_MAINBOARD_HPP
