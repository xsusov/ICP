#include "boardfield.h"
#include "constants.h"

using namespace labyrinth;

BoardField::BoardField()
    :  path{ false, false, false, false }
{
}

BoardField::BoardField(const int x, const int y)
    : posX{x},
      posY{y},
      path{ false, false, false, false },
      playerSlot{nullptr, nullptr, nullptr, nullptr}
{
}

int BoardField::getPosX()
{
    return posX;
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
    return playerSlot[pos] != nullptr ? playerSlot[pos]->draw() : opened;
}

void BoardField::printRow(const int row)
{
    if( row < 0 || row > 4){
        return void();
    }

    switch(row){
        case(0):
            std::cout << closed << closed << getPath(labyrinth::north) << closed << closed << "fuck";
            break;
        case(1):
            std::cout << closed << getPlayerSlot(0) << opened << getPlayerSlot(1) << closed;
            break;
        case(2):
            std::cout << getPath(labyrinth::west) << opened << opened << opened << getPath(labyrinth::east);
            break;
        case(3):
            std::cout << closed << getPlayerSlot(2) << opened << getPlayerSlot(3) << closed;
            break;
        case(4):
            std::cout << closed << closed << getPath(labyrinth::south) << closed << closed;
    };
}

void BoardField::appendRow(const int row, std::string& str)
{
    if( row < 0 || row > 4){
        return void();
    }

    switch(row){
        case(0):
            str.push_back(closed);
            str.push_back(closed);
            str.push_back(getPath(labyrinth::north));
            str.push_back(closed);
            str.push_back(closed);
            break;
        case(1):
            str.push_back(closed);
            str.push_back(getPlayerSlot(0));
            str.push_back(opened);
            str.push_back(getPlayerSlot(1));
            str.push_back(closed);
            break;
        case(2):
            str.push_back(getPath(labyrinth::west));
            str.push_back(opened);
            str.push_back(opened);
            str.push_back(opened);
            str.push_back(getPath(labyrinth::east));
            break;
        case(3):
            str.push_back(closed);
            str.push_back(getPlayerSlot(2));
            str.push_back(opened);
            str.push_back(getPlayerSlot(3));
            str.push_back(closed);
            break;
        case(4):
            str.push_back(closed);
            str.push_back(closed);
            str.push_back(getPath(labyrinth::south));
            str.push_back(closed);
            str.push_back(closed);
            break;
    };
}
