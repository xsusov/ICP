#include "gameboard.h"
#include "constants.h"

using namespace labyrinth;

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
    field = new BoardField*[totalFields];
    for( int i = 0; i < totalFields; i++){
        field[i] = nullptr;
    }

    /// new field will be filled with randomly selected board fields, given some rules (corner field must be LBoardField fe.)
}

GameBoard::~GameBoard()
{
    for( int i = 0; i < totalFields; i++){
        delete field[i];
    }

    delete[] field;
}

inline int GameBoard::pos(const int x, const int y)
{
    return y * size + x;
}

inline bool GameBoard::isCorner(const int pos)
{
    return pos == 0 || pos  == size - 1 || pos == totalFields - size || pos == totalFields - 1;
}

bool GameBoard::isPathOpen(const int xFrom, const int yFrom, const int direction)
{
    BoardField *from = getField( xFrom, yFrom );
    if( from == nullptr )
        return false;

    BoardField *to = getNeighbour( from, direction );

    return from->isOpen( direction ) && to->isOpen( opositeDirection(direction) );
}


void GameBoard::draw()
{
    std::string line {""};

    for( int y = 0; y < size; ++y){
        for( int i = 0; i < 5; i++){
            for( int x = 0; x < size; ++x){
                getField(x,y)->appendRow(i, line);
            }
            std::cout << line << std::endl;
            line.clear();
        }
    }
}

void GameBoard::setUpFields()
{
    int corner = 1;

    for( int y = 0; y < size; ++y){
        for( int x = 0; x < size; ++x){
            if( isCorner(pos(x,y)) ){
                std::cout << x << y << std::endl;

                field[y * size + x] = new LBoardField(x,y);
                field[y * size + x]->rotate(corner);
                field[y * size + x]->draw();
                corner += corner;
                if( corner > 4 )
                    corner--;
            }
            else{
                field[y * size + x] = new BoardField(x,y);
            }
        }
    }
}

BoardField *GameBoard::getNeighbour(BoardField *from, const int direction)
{
    int neighbourX = from->getPosX(),
        neighbourY = from->getPosY();

    switch( direction ){
        case( north ):
            neighbourY--;
            break;
        case( east ):
            neighbourX++;
            break;
        case( south ):
            neighbourY++;
            break;
        case( west ):
            neighbourX--;
            break;
        default:
            return nullptr;
    }

    return getField( neighbourX, neighbourY );
}

BoardField* GameBoard::getField( int posX, int posY )
{
    if( posX < 0 || posX >= size || posY < 0 || posY >= size )
        return nullptr;

    return field[ posY * size + posX ];
}

