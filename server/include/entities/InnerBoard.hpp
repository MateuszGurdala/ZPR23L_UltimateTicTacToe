#ifndef ULTIMATETICTACTOESERVER_INNERBOARD_HPP
#define ULTIMATETICTACTOESERVER_INNERBOARD_HPP

#include <vector>
#include <array>
#include <memory>
#include "BoardBase.hpp"

/*  Class: InnerBoard
    Class describing sub board which is nested inside Main Board. It includes unique pointer to 2 dimensional board of chars.
    See also:
    <MainBoard>
 */
class InnerBoard : public BoardBase{
private:
    std::unique_ptr<std::unique_ptr<char[]>[]> playBoard;
    /*  Function: ToJson
    Fills board with whitespaces.
     */
    void FillBoard() override;

public:
/*  Constructor: InnerBoard
    Constructor which takes size of board as parameter. Creates empty board 2 dimensional array
 */
InnerBoard(int boardSize);
std::string ToString() const;
auto GetLeftDiagonalValues(Point& playBoardCoordinates, Point& innerBoardRowAndColumn);
auto GetRightDiagonalValues(Point& playBoardCoordinates, Point& innerBoardRowAndColumn);
auto GetHorizontalValues(Point& playBoardCoordinates, Point& innerBoardRowAndColumn);
auto GetVerticalValues(Point& playBoardCoordinates, Point& innerBoardRowAndColumn);
/*  Function: ToJson
    Converts board to json format which is used in communication with the client.
    Parameters:

    isNested - boolean value indicating if json is nested inside other json, because it has impact on structure of json
 */
std::string ToJson(bool isNested) override;
/*  Function: PlaceFigure
    function which places a figure on given coordinate provided as parameter.

    Parameters:

    coordinates - (x,y) coordinates of the board where the figure will be placed
    figure - symbol which will be placed inside the board

    See also:
    <Point>
*/
void PlaceFigure(Point& coordinates, char &figure);
};

#endif //ULTIMATETICTACTOESERVER_INNERBOARD_HPP
