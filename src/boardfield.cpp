/**
 * @project LABYRINTH2015
 * ICP project
 * @class BoardField
 * @author xsusov01
 * @email  xsusov01@stud.fit.vutbr.cz
 * @author xbandz00
 * @email  xbandz00@stud.fit.vutbr.cz
 * @file boardfield.cpp
 * @date 2015/05/10
 * @brief abstract base class for all types of boardfields
*/
#include "boardfield.h"

using namespace labyrinth;

/**
 * @brief BoardField::BoardField
 *        default boardfield constructor template
 */
BoardField::BoardField()
    :  path{ false, false, false, false }
{
}

/**
 * @brief BoardField::BoardField parametrized constructor
 * @param x - X position of new biardfield
 * @param y - Y position of new biardfield
 * @param pathNorth - open/cloesd for moving to boardfield north from new boardfield
 * @param pathEast  - open/cloesd for moving to boardfield east from new boardfield
 * @param pathSouth - open/cloesd for moving to boardfield south from new boardfield
 * @param pathWest  - open/cloesd for moving to boardfield west from new boardfield
 * @param item      - item on new field (empty by default)
 */
BoardField::BoardField(const int x, const int y, bool pathNorth, bool pathEast, bool pathSouth, bool pathWest, GameItem *item)
    : posX{x},
      posY{y},
      path{ pathNorth, pathEast, pathSouth, pathWest },
      playerSlot{nullptr, nullptr, nullptr, nullptr},
      item{item}
{
}

/**
 * @brief BoardField::~BoardField
 *        desturctor
 */
BoardField::~BoardField()
{

}

/**
 * @brief BoardField::isOpen
 *        checks if path in given direction is opened for moving
 * @param direction
 * @return true if path in direction is on boardfield opened
 */
bool BoardField::isOpen( const int direction ) const
{
    return path[roundDirection(direction)];
}

/**
 * @brief BoardField::getPath
 *        checks path from boardfield in given direction
 * @param direction of boardfield path
 * @return char of open or closed path
 */
char BoardField::getPath(const int direction)
{
    return path[direction] ? labyrinth::opened : labyrinth::closed;
}

/**
 * @brief BoardField::getStr
 *        transforms boardfield to string representation
 * @return string representation of BoardField
 */
std::string BoardField::getStr()
{
    std::string fieldStr;
    for(int i = 0; i <= maxRow; i++){
        appendRow(i, fieldStr );
        fieldStr += '\n';
    }

    return fieldStr;
}

/**
 * @brief BoardField::draw
 *        prints boardfield on standard output
 */
void BoardField::draw()
{
    std::cout << getStr() << std::endl;
}

/**
 * @brief BoardField::getPlayerSlot
 * @param pos - player position in boardfield (corners)
 * @return player's figure on given position or empty space
 */
char BoardField::getPlayerSlot(const int pos)
{
    return playerSlot[pos] != nullptr ? playerSlot[pos]->getFigure() : opened;
}

/**
 * @brief BoardField::drawItem
 * @return boardfield's item figure or empty space
 */
char BoardField::drawItem()
{
    return item != nullptr ? item->getFigure() : opened;
}

/**
 * @brief BoardField::getLogItem
 * @return item for logging (it's figure or zero)
 */
char BoardField::getLogItem()
{
    return item != nullptr ? item->getFigure() : '0';
}

/**
 * @brief BoardField::appendRow
 * @param row number (0-4) of 5*5 boardfield
 * @param str string for appending target boardfield's row
 */
void BoardField::appendRow(const int row, std::string& str)
{
    if( row < minRow || row > maxRow)
        return;

    switch(row){
        case(0):
            str += {closed, closed, getPath(north), closed, closed};
            break;
        case(1):
            str += {closed, getPlayerSlot(north), opened, getPlayerSlot(east), closed};
            break;
        case(2):
            str += {getPath(west), opened, drawItem(), opened, getPath(east)};
            break;
        case(3):
            str += {closed, getPlayerSlot(west), opened, getPlayerSlot(south), closed};
            break;
        case(4):
            str += {closed, closed, getPath(south), closed, closed};
            break;
    };
}

/**
 * @brief BoardField::swapPlayers
 *        swaps all players between two boardfield
 * @param swapField boardfield to swap players with
 */
void BoardField::swapPlayers(BoardField &swapField)
{
    Player *tmp = nullptr;
    for( int i = 0; i < 4; i++){
        tmp = playerSlot[i];
        playerSlot[i] = swapField.playerSlot[i];
        if( swapField.playerSlot[i] != nullptr ){
            playerSlot[i]->placeOnField(this);
        }
        swapField.playerSlot[i] = tmp;
        if( swapField.playerSlot[i] != nullptr ){
            swapField.playerSlot[i]->placeOnField(&swapField);
        }
    }
}

/**
 * @brief BoardField::rotate
 *        rotates boardfield for 90° for x-times
 * @param x - number of rotations
 */
void BoardField::rotate(int x)
{
    x %= 4;
    if( !x )
        return;

    std::rotate( path.rbegin(), path.rbegin() + x, path.rend());
}

/**
 * @brief BoardField::setPlayer
 *        changes player on position of given player to new one
 * @param oldPlayer
 * @param newPlayer
 */
void BoardField::setPlayer(Player *oldPlayer, Player *newPlayer)
{
    for( int i = 0; i < maxPlayers; i++){
        if( playerSlot[i] == oldPlayer ){
            playerSlot[i] = newPlayer;
            return;
        }
    }
}

/**
 * @brief BoardField::addPlayer
 *        adds player to boardfield on first free position
 * @param player
 */
void BoardField::addPlayer(Player *player)
{
    setPlayer(nullptr, player);
}

/**
 * @brief BoardField::removePlayer
 *        removes player from field
 * @param player
 */
void BoardField::removePlayer(Player *player)
{
    setPlayer(player, nullptr);
}

/**
 * @brief BoardField::updateDirection
 *        changes boardfield's position coordinates posX and posY depending on direction
 * @param direction
 */
void BoardField::updateDirection( const int direction )
{
  switch( roundDirection(direction)){
      case( north ): decPosY();
                     return;
      case( east ):  incPosX();
                     return;
      case( south ): incPosY();
                     return;
      case( west ):  decPosX();
                     return;
  }
}
