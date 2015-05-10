/**
 * @project LABYRINTH2015
 * ICP project
 * @class GameBoard
 * @author xsusov01
 * @email  xsusov01@stud.fit.vutbr.cz
 * @author xbandz00
 * @email  xbandz00@stud.fit.vutbr.cz
 * @file gameboard.cpp
 * @date 2015/05/10
 * @brief class for wrapping board of game model as vector of boardfields and free field used for changing board placement
*/
#include <random>
#include "constants.h"
#include "strings.h"
#include "gameboard.h"

using namespace labyrinth;

/**
 * @brief random_bool function for random distribution generation for items setup
 * @param ratio - ratio used for check against generated value
 * @return boolean value as result of comparsion of ratio parameter and randomly generated number
 */
bool random_bool(const float ratio)
{
    int random = std::rand() % 101;
    return random < static_cast<int>(ratio * 100);
}

/**
 * @brief GameBoard::GameBoard constructor
 * @param size - number of rows and columns on board
 * @see   GameBoard::setUpFields()
 */
GameBoard::GameBoard( const int size )
    : size{size},
      max{size - 1},
      totalFields{size * size},
      freeField{nullptr}
{
    if( size < labyrinth::boardMinSize || size > labyrinth::boardMaxSize ){
        throw expWrongSize; /// size is limited by rules of game to be in range <5;11>
    }

    if( !(size%2) ){        /// size is also limited to be odd number only
        throw expWrongEvenSize;
    }

    /// reserve space in field vector for all new field (will be added by setUpFields() method later)
    field.reserve(totalFields);
    for( int i = 0; i < totalFields; i++){
        field.push_back(nullptr);
        /// new field will be filled with randomly selected board fields, given some rules (corner field must be LBoardField fe.)
    }
}

/**
 * @brief GameBoard::~GameBoard destructor
 */
GameBoard::~GameBoard()
{
    for( auto curField : field){
        delete curField;
    }

    delete freeField;
}

std::string GameBoard::getStr()
{
    std::string str {""};
    for( int y = 0; y < size; ++y){
        for( int i = 0; i < 5; i++){
            for( int x = 0; x < size; ++x){
                getField(x,y)->appendRow(i, str);
            }
            str += '\n';
        }
    }

    return str;
}

void GameBoard::draw()
{
    std::cout << getStr() << std::endl;
    std::cout << strFreeField << std::endl << freeField->getStr() << std::endl;
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
            }

            field[i]->rotate( rotateDistribution(randGenerator));
            if(isEdge( x, y ))
                field[i]->rotateInside(x, y, max);
            i++;
        }
    }

    freeField = makeRandBoardfield(-1, -1, rotateDistribution(randGenerator));
    freeField->rotate( rotateDistribution(randGenerator));
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

void GameBoard::setField(const int posX, const int posY, BoardField *newField)
{
    field[pos(posX, posY)] = newField;
}

BoardField *GameBoard::makeRandBoardfield(const int x, const int y, const int randNum)
{
    switch(randNum % 3){
        case(0):
            return new LBoardField(x, y);
        case(1):
            return new TBoardField(x, y);
        case(2):
            return new IBoardField(x, y);
        default:
            return nullptr;
    }
}

BoardField *GameBoard::makeTargetBoardField(const int x, const int y, const int logNum, GameItem *item)
{
    BoardField *newField {nullptr};
    if( logNum >= 6 ){
        newField = new TBoardField(x, y, item);
        newField->rotate(logNum - 6);
    }
    else if( logNum >= 2 ){
        newField = new LBoardField(x, y, item);
        newField->rotate(logNum - 2);
    }
    else{
        newField = new IBoardField(x, y, item);
        newField->rotate(logNum );
    }

    return newField;
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

    return field[ pos(posX, posY) ];
}

void GameBoard::rotateFreeField(const int rotate)
{
    freeField->rotate(rotate);
}

void GameBoard::shift(const int first, const int last, const int offset, const int direction, const int lastX, const int lastY )
{
    BoardField *tmp = field[ first ];

    for( int i = first; i != last; i += offset ){
         field[ i ] = field[ i + offset];
         field[ i ]->updateDirection( direction );
    }
    field[ last ] = freeField;
    field[ last ]->updatePos( lastX, lastY );
    tmp->swapPlayers(*field[ last ]);
    freeField = tmp;
    freeField->updatePos(-1,-1);

}

void GameBoard::shift(const int num, const int direction)
{
    switch( direction ){
        case north:
            return shift( num, max * size + num, size, north, num, max);
        case east:
            return shift( num * size  + max, num * size, -1, east, 0, num );
        case south:
            return shift( max * size + num, num, -size, south, num, 0);
        case west:
            return shift( num * size, num * size + max , 1, west, max, num );
    }
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

bool GameBoard::isWalkable(BoardField *from, const int direction ) const
{
    if( from == nullptr || !from->isOpen(direction))
        return false;

    BoardField *to = getNeighbour(*from, direction);
    if( to == nullptr || !to->isOpen(opositeDirection(direction)) )
        return false;

    return true;
}

bool GameBoard::movePlayer(Player *player, const int direction)
{
    if(player == nullptr)
        return false;

    BoardField *from = player->getCurField();
    if( !isWalkable( from, direction))
        return false;

    BoardField *to = getNeighbour(*from, direction);
    from->removePlayer(player);
    to->addPlayer(player);
    player->placeOnField(to);
    return true;
}
