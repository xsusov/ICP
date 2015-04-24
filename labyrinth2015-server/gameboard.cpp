#include "constants.h"
#include "gameboard.h"
#include <random>

using namespace labyrinth;

bool random_bool(const float ratio)
{
    int random = std::rand() % 101;
    return random < static_cast<int>(ratio * 100);
}

GameBoard::GameBoard( const int size = 7 )
    : size{size},
      max{size - 1},
      totalFields{size * size},
      freeField{nullptr}
{
    if( size < labyrinth::boardMinSize || size > labyrinth::boardMaxSize ){
        throw "Wrong board size. Please, select size in range from 5 to 11.";
    }

    if( !(size%2) ){
        throw "Wrong board size. Board size oughts to be odd number.";
    }

    field.reserve(totalFields);
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
}

inline int GameBoard::pos(const int x, const int y)
{
    return y * size + x;
}

inline bool GameBoard::isCorner(const int pos)
{
    return !pos|| pos == max || pos == totalFields - size || pos == totalFields - 1;
}

bool GameBoard::isPathOpen(const int xFrom, const int yFrom, const int direction)
{
    BoardField *from = getField( xFrom, yFrom );
    if( from == nullptr )
        return false;

    BoardField *to = getNeighbour( *from, direction );
    if( to == nullptr )
        return false;

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
    int curPos = 0;
    float ratio = (float)items.size() / ((float)(totalFields + 1));
    try{
    for( int y = 0; y < size; ++y){
        for( int x = 0; x < size; ++x){
            if( i >=  items.size())
                return;
            curPos = pos(x, y);
            if((totalFields - curPos <=  (items.size() - i)) || random_bool(ratio)){
                field[curPos]->setItem( items[i++] );
            }
        }
    }
    }
    catch( std::exception &e){
       std::cerr << e.what();
    }
    if( i >=  items.size())
        return;

    freeField->setItem( items[0] );
}

void GameBoard::setUpPlayers(std::vector<Player *> &players)
{
    int startingFieldsX[4] { 0, max, 0, max};
    int startingFieldsY[4] { 0, 0, max, max};
    BoardField *startingField;
    int i = 0;
    for( Player *player: players ){
        startingField = getField( startingFieldsX[i], startingFieldsY[i] );
        startingField->addPlayer(player);
        player->placeOnField(startingField);
        i++;
    }
}

void GameBoard::setUpFields()
{
    std::default_random_engine randGenerator;
    std::uniform_int_distribution<int> rotateDistribution(0,3);
    int i = 0;
    for( int y = 0; y < size; ++y){
        for( int x = 0; x < size; ++x){
            if( isCorner(i)){    // corner field - allways must be L-field, with open path towards inside labyrinth
               field[i] = new LBoardField(x,y);
            }
            else if( !(x % 2 || y % 2)){ // odd row and odd colum - T-field
               field[i] = new TBoardField(x,y);
            }
            else{
                switch(rotateDistribution(randGenerator) % 3){
                    case(0):
                        field[i] = new LBoardField(x,y);
                        break;
                    case(1):
                        field[i] = new TBoardField(x,y);
                        break;
                    case(2):
                        field[i] = new IBoardField(x,y);
                        break;
                }
            }

            field[i]->rotate( rotateDistribution(randGenerator));
            if(isEdge( x, y ))
                field[i]->rotateInside(x, y, max);
            i++;
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

    freeField->rotate( rotateDistribution(randGenerator));
}

BoardField *GameBoard::getNeighbour(const BoardField &from, const int direction) const
{
    int neighbourX = from.getPosX(),
        neighbourY = from.getPosY();

    if( !updateDirection( neighbourX, neighbourY, direction ))
        return nullptr;

    return getField( neighbourX, neighbourY );
}

BoardField* GameBoard::getField( int posX, int posY ) const
{
    if( posX < 0 || posX > max || posY < 0 || posY > max )
        return nullptr;

    return field[ posY * size + posX ];
}

void GameBoard::rotateFreeField(const int rotate)
{
    freeField->rotate(rotate);
}

void GameBoard::shiftColumn(const int col, const bool up)
{
    const int first { up ? col :  max * size + col };
    const int last  { up ? max * size + col : col };
    const int offset{ up ? size : -size };
    const int direction{ up ? north : south };
    BoardField *tmp = field[ first ];

    for( int i = first; i != last; i += offset ){
       (field[ i ] = field[ i + offset])->updateDirection( direction );;
        //field[ i ]->updateDirection( direction );
    }
    freeField->updatePos(col, up ? max : 0);
    freeField->swapPlayers(*tmp);
    field[ last ] = freeField;
    freeField = tmp;
    freeField->updatePos(-1,-1);
}

void GameBoard::shiftRow(const int row, bool left )
{
    int i = 0;
    const int first { left ? row * size + max : row * size };
    const int last  { left ? row * size : row * size + max };

    BoardField *tmp = field[ last ];

    if( left ){
        for( i = 0; i < max; i++){
            field[ row * size + i ] = field[ row * size + i + 1 ];
            field[ row * size + i ]->decPosX();
        }
        freeField->updatePos(max, row);
    }
    else{
        for( i = max; i >= 0; i--){
            field[ row * size + i ] = field[ row * size + i - 1 ];
            field[ row * size + i ]->incPosX();
        }
        freeField->updatePos(0, row);
    }

    freeField->swapPlayers(*tmp);
    field[ first ] = freeField;
    freeField = tmp;
    freeField->updatePos(-1,-1);
}

int GameBoard::getSize()
{
    return size;
}

void GameBoard::shift(const char shiftMode, const int num, const bool direction)
{
    if( shiftMode == 'r')
        shiftRow(num, direction);
    else if( shiftMode == 'c')
        shiftColumn(num, direction);
}

bool GameBoard::isEdge(const int x, const int y) const
{
  return !x || !y || x == max || y == max;
}

bool GameBoard::isEdgingDirection(const BoardField &from, const int direction) const
{
  return getNeighbour(from, direction) != nullptr;
}

bool GameBoard::updateDirection( int &x, int &y, const int direction )
{
  switch( direction ){
      case( north ):
          y--;
          break;
      case( east ):
          x++;
          break;
      case( south ):
          y++;
          break;
      case( west ):
          x--;
          break;
      default:
          return false;
  }
  return true;
}
