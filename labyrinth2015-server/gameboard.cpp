#include "gameboard.h"

GameBoard::GameBoard(const int size)
    : size{size}
{
    if( size < labyrinth::boardMinSize || size > labyrinth::boardMaxSize ){
        throw "Wrong board size";
    }

    /// @todo: new board fields placement
    field = new BoardField[size*size];
    /// new field will be filled with randomly selected board fields, given some rules (corner field must be LBoardField fe.)
}
