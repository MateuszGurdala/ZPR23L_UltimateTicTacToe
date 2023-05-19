
#include <vector>
#include "../../include/entities/BoardBase.hpp"

unsigned int BoardBase::GetBoardSize() const {
    return boardSize;
}

BoardBase::BoardBase(unsigned int boardSize) : boardSize(boardSize){

    if(boardSize <= 0)
    {
        throw std::invalid_argument("size of board must be positive");
    }
}

void BoardBase::VerifyFigure(char figure) {
    if(figure != 'X' && figure != 'O')
    {
        throw std::invalid_argument("only allowed figures are X and O");
    }
}

void BoardBase::VerifyCoordinates(Point coordinates) const {
    if(coordinates.x < 0 || coordinates.x >= boardSize || coordinates.y < 0 || coordinates.y >= boardSize)
    {
        throw std::out_of_range("Coordinates are out of bounds of board");
    }
}

auto BoardBase::GetLeftDiagonalValues(Point &chosenCoordinates, std::vector<std::vector<char>>& board) const {
    std::vector<char> diagonalSymbols;
    unsigned int tempX = (int)chosenCoordinates.x;
    for(unsigned int columnUpIndex = chosenCoordinates.y; columnUpIndex < boardSize; columnUpIndex++)
    {
        diagonalSymbols.emplace_back(board[tempX][columnUpIndex]);
        tempX--;
    }
    tempX = (int)chosenCoordinates.x - 1;
    for(int columnDownIndex = (int)chosenCoordinates.y - 1; columnDownIndex >= 0; columnDownIndex--)
    {
        diagonalSymbols.emplace_back(board[tempX][columnDownIndex]);
        tempX--;
    }
    return diagonalSymbols;
}

auto BoardBase::GetRightDiagonalValues(Point &chosenCoordinates, std::vector<std::vector<char>>& board) const {
    std::vector<char> diagonalSymbols;
    unsigned int tempX = (int)chosenCoordinates.x;
    for(unsigned int columnUpIndex = chosenCoordinates.y; columnUpIndex < boardSize; columnUpIndex++)
    {
        diagonalSymbols.emplace_back(board[tempX][columnUpIndex]);
        tempX++;
    }
    tempX = (int)chosenCoordinates.x - 1;
    for(int columnDownIndex = (int)chosenCoordinates.y - 1; columnDownIndex >= 0; columnDownIndex--)
    {
        diagonalSymbols.emplace_back(board[tempX][columnDownIndex]);
        tempX++;
    }
    return diagonalSymbols;
}

auto BoardBase::GetHorizontalValues(Point &chosenCoordinates, std::vector<std::vector<char>>& board) const {
    std::vector<char> horizontalSymbols;
    for(unsigned int rowRightIndex = chosenCoordinates.x; rowRightIndex < boardSize; rowRightIndex++ )
    {
        horizontalSymbols.emplace_back(board[chosenCoordinates.x][rowRightIndex]);
    }
    for(int columnDownIndex = (int)chosenCoordinates.x; columnDownIndex >= 0; columnDownIndex--)
    {
        horizontalSymbols.emplace_back(board[chosenCoordinates.x][columnDownIndex]);
    }
    return horizontalSymbols;
}

auto BoardBase::GetVerticalValues(Point &chosenCoordinates, std::vector<std::vector<char>>& board) const {
    std::vector<char> verticalSymbols;
    for(unsigned int columnUpIndex = chosenCoordinates.y; columnUpIndex < boardSize; columnUpIndex++)
    {
        verticalSymbols.emplace_back(board[chosenCoordinates.x][columnUpIndex]);
    }
    for(int columnDownIndex = (int)chosenCoordinates.y; columnDownIndex >= 0; columnDownIndex--)
    {
        verticalSymbols.emplace_back(board[chosenCoordinates.x][columnDownIndex]);
    }
    return verticalSymbols;
}

