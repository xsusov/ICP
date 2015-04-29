#include "constants.h"
#include "strings.h"
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
        throw expWrongSize;
    }

    if( !(size%2) ){
        throw expWrongEvenSize;
    }

    field.reserve(totalFields);
    for( int i = 0; i < totalFields; i++){
        field.push_back(nullptr);
    }
    /// new field will be filled with randomly selected board fields, given some rules (corner field must be LBoardField fe.)
}

GameBoard::~GameBoard()
{
    for( auto curField : field){
        delete curField;
    }
}

inline int GameBoard::pos(const int x, const int y)
{
    return y * size + x;
}

inline bool GameBoard::isCorner(const int pos)
{
    return !pos || pos == max || pos == totalFields - size || pos == totalFields - 1;
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

    std::cout << std::endl << strFreeField << std::endl;
    freeField->draw();
}

void GameBoard::setUpItems(std::vector<GameItem *> &items )
{
    std::size_t i = 0;
    int curPos = 0;
    float ratio = static_cast<float>(items.size()) / static_cast<float>(totalFields + 1);
    try{
    for( int y = 0; y < size; ++y){
        for( int x = 0; x < size; ++x){
            if( i >=  items.size())
                return;
            curPos = pos(x, y);
            if((static_cast<std::size_t>(totalFields - curPos) <=  (items.size() - i)) || random_bool(ratio)){
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

    freeField->setItem( items[i] );
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
                field[i] = makeRandBoardfield(x, y, rotateDistribution(randGenerator));
               /*
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
                */
            }

            field[i]->rotate( rotateDistribution(randGenerator));
            if(isEdge( x, y ))
                field[i]->rotateInside(x, y, max);
            i++;
        }
    }

    freeField = makeRandBoardfield(-1, -1, rotateDistribution(randGenerator));
   /*
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
    }*/

    freeField->rotate( rotateDistribution(randGenerator));
}

BoardField *GameBoard::makeRandBoardfield(const int x, const int y, const int randNum)
{
    switch(randNum % 3){
        case(0):
            return new LBoardField(x,y);
        case(1):
            return new TBoardField(x,y);
        case(2):
            return new IBoardField(x,y);
        default:
            return nullptr;
    }
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
        field[ i ] = field[ i + offset];
        field[ i ]->updateDirection( direction );
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
    ( shiftMode == 'r') ? shiftRow(num, direction) : shiftColumn(num, direction);
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
    // @todo -> look at border limit
  switch( roundDirection(direction )){
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
    }
  return true;
}

bool GameBoard::movePlayer(Player *player, const int direction)
{
    if(player == nullptr)
        return false;

    BoardField *from = player->getCurField();
    if( from == nullptr || !from->isOpen(direction))// || isEdgingDirection(*from,direction))
        return false;

    BoardField *to = getNeighbour(*from, direction);
    if( to == nullptr || !to->isOpen(opositeDirection(direction)) )
        return false;

    from->removePlayer(player);
    to->addPlayer(player);
    player->placeOnField(to);
    return true;
}
