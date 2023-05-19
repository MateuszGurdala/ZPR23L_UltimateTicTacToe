#ifndef ULTIMATETICTACTOESERVER_INNERBOARD_HPP
#define ULTIMATETICTACTOESERVER_INNERBOARD_HPP

#include <vector>
#include <array>
#include <memory>
#include "BoardBase.hpp"

/*  Class: InnerBoard
    Class describing sub board which is nested inside Main Board. It includes vector to 2 dimensional vector of chars.
    See also:
    <MainBoard>
 */
class InnerBoard : public BoardBase{
private:
    std::vector<std::vector<char>> playBoard;
    /*  Function: ToJson
    Fills board with whitespaces.
     */
    void FillBoard() override;

public:
/*  Constructor: InnerBoard
    Constructor which takes size of board as parameter. Creates empty board 2 dimensional array
 */
InnerBoard(unsigned int boardSize);
const std::vector<std::vector<char>>& GetPlayBoard() const;
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

/*  Function: GetCell
    Gets element at given cell.

    Parameters:

    coordinates - (x,y) coordinates of the board where the figure will be placed
*/
char GetCell(Point coordinates);
};

#endif //ULTIMATETICTACTOESERVER_INNERBOARD_HPP
