#include "gameboard.h"

GameBoard::GameBoard( const int size = 7 )
    : size{size},
      totalFields{size * size}
{
    if( size < labyrinth::boardMinSize || size > labyrinth::boardMaxSize ){
        throw "Wrong board size. Please, select size in range from 5 to 11.";
    }

    if( !(size%2) ){
        throw "Wrong board size. Board size oughts to be odd number.";
    }

    /// @todo: new board fields placement
    field = new BoardField[totalFields];
    for( int y = 0; y < size; ++y){
        for( int x = 0; x < size; ++x){
            field[y * size + x] = BoardField(x,y);
        }
    }

    /// new field will be filled with randomly selected board fields, given some rules (corner field must be LBoardField fe.)
}

void GameBoard::draw()
{
    std::string line {""};

    for( int y = 0; y < size; ++y){
        for( int i = 0; i < 5; i++){
            for( int x = 0; x < size; ++x){
                getField(x,y).appendRow(i, line);
            }
            std::cout << line << std::endl;
            line.clear();
        }
    }
}

void GameBoard::setUpFields()
{
    /*
    for( int x = 0; x < totalFields; ++x){
        for( int y = 0; y < size; ++y){
            if( (x == 0 || x==(size-1)) && (y==(size-1) || y==0))
                field[x+y] = LBoardField( x, y );
            else
                field[x][y] = BoardField( x, y );
        }
        std::cout << std::endl;
    }
    */
}

BoardField& GameBoard::getField( int posX, int posY )
{
    return field[ posY * size + posX ];
}
