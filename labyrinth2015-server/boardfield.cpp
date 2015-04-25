#include <algorithm>
#include <vector>
#include "constants.h"
#include "boardfield.h"


using namespace labyrinth;

BoardField::BoardField()
    :  path{ false, false, false, false }
{
}

BoardField::BoardField(const int x, const int y, bool pathNorth, bool pathEast, bool pathSouth, bool pathWest, GameItem *item)
    : posX{x},
      posY{y},
      path{ pathNorth, pathEast, pathSouth, pathWest },
      playerSlot{nullptr, nullptr, nullptr, nullptr},
      item{item}
{
}

BoardField::~BoardField()
{

}

char BoardField::getPath(const int direction)
{
    return path[direction] ? labyrinth::opened : labyrinth::closed;
}

void BoardField::draw()
{
    for(int i = 0; i < 5; i++){
        printRow(i);
        std::cout << std::endl;
    }
}

char BoardField::getPlayerSlot(const int pos)
{
    return playerSlot[pos] != nullptr ? playerSlot[pos]->getFigure() : opened;
}

char BoardField::drawItem()
{
    return item != nullptr ? item->getFigure() : opened;
}

void BoardField::printRow(const int row)
{
    if( row < 0 || row > 4){
        return void();
    }

    switch(row){
        case(0):
            std::cout << closed << closed << getPath(labyrinth::north) << closed << closed;
            break;
        case(1):
            std::cout << closed << getPlayerSlot(0) << opened << getPlayerSlot(1) << closed;
            break;
        case(2):
            std::cout << getPath(labyrinth::west) << opened << drawItem() << opened << getPath(labyrinth::east);
            break;
        case(3):
            std::cout << closed << getPlayerSlot(2) << opened << getPlayerSlot(3) << closed;
            break;
        case(4):
            std::cout << closed << closed << getPath(labyrinth::south) << closed << closed;
            break;
    };
}

void BoardField::appendRow(const int row, std::string& str)
{
    if( row < 0 || row > 4){
        return void();
    }

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

void BoardField::setItem(GameItem *newItem)
{
    item = newItem;
}

GameItem *BoardField::getItem()
{
    return item;
}

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

bool BoardField::isOpen( int direction )
{
    if( direction < north || direction > west )
        return false;

    return path[direction] == opened;
}

void BoardField::rotate(int x)
{
    x %= 4;
    if( !x )
        return;

    std::rotate( path.rbegin(), path.rbegin() + x, path.rend());
}

void BoardField::addPlayer(Player *player)
{
    for( int i = 0; i < 4; i++){
        if( playerSlot[i] == nullptr ){
            playerSlot[i] = player;
            return;
        }
    }
}

void BoardField::removePlayer(Player *player)
{
    for( int i = 0; i < 4; i++){
        if( playerSlot[i] == player ){
            playerSlot[i] = nullptr;
            return;
        }
    }
}

void BoardField::updateDirection( const int direction )
{
  switch( direction % 4 ){
      case( north ):
          decPosY();
          break;
      case( east ):
          incPosX();
          break;
      case( south ):
          incPosY();
          break;
      case( west ):
          decPosY();
          break;
      default:
          return;
  }
}

void BoardField::removeItem()
{
    item = nullptr;
}

