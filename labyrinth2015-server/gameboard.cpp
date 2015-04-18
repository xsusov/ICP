#include "constants.h"
#include "gameboard.h"
#include <random>

using namespace labyrinth;

bool random_bool(const float ratio)
{
    int random = std::rand() % 101;
    if (random < ratio * 100) return true;
    return false;
}

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

    std::cout << std::endl << "Free boardfield:" << std::endl;
    freeField->draw();
}

void GameBoard::setUpItems(std::vector<GameItem *> &items )
{
    int i = 0;

    for( int y = 0; y < size; ++y){
        for( int x = 0; x < size; ++x){
            if( i >=  items.size())
                return;
            if(random_bool(items.size()/((float)totalFields+1)) || (totalFields - (y * size + x) <=  items.size() - i))
            {
                field[y * size + x]->setItem( items[(y * size + x)] );
                i++;
            }
        }
    }

    if( i >=  items.size())
        return;

    freeField->setItem( items[0] );
}

void GameBoard::setUpFields()
{
    int corner = 1;

    std::default_random_engine randGenerator;
    std::uniform_int_distribution<int> rotateDistribution(0,3);

    for( int y = 0; y < size; ++y){
        for( int x = 0; x < size; ++x){
            if( isCorner(pos(x,y)) ){                       // corner field - allways must be L-field, with open path towards inside labyrinth
                field[y * size + x] = new LBoardField(x,y);
                field[y * size + x]->rotate(corner);
                corner += corner;
                if( corner > 4 )
                    corner--;
            }
            else if( !(x % 2 || y % 2)){           // odd row and odd colum - T-field
                field[y * size + x] = new TBoardField(x,y);

                // @todo extract method for this
                if( !x )
                    field[y * size + x]->rotate(3);
                else if( !y ){
                    continue;
                }
                else if( x == size - 1 ){
                    field[y * size + x]->rotate(1);
                }
                else if( y == size - 1 ){
                    field[y * size + x]->rotate(2);
                }
                else{
                    field[y * size + x]->rotate( rotateDistribution(randGenerator));
                }
            }
            else{
                switch(rotateDistribution(randGenerator) % 3){
                    case(0):
                        field[y * size + x] = new LBoardField(x,y);
                        break;
                    case(1):
                        field[y * size + x] = new TBoardField(x,y);
                        break;
                    case(2):
                        field[y * size + x] = new IBoardField(x,y);
                        break;
                }

                field[y * size + x]->rotate( rotateDistribution(randGenerator));
            }
        }
    }

    switch(rotateDistribution(randGenerator) % 3){
        case(0):
            freeField = new LBoardField(-1, -1);
            break;
        case(1):
            freeField = new TBoardField(-1, -1);
            break;
        case(2):
            freeField = new IBoardField(-1, -1);
            break;
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

