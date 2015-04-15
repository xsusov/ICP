#ifndef LBOARDFIELD_H
#define LBOARDFIELD_H

#include <iostream>
#include "boardfield.h"

class LBoardField : public BoardField
{
public:
    LBoardField(const int x,const int y );
    //char getPath(const int direction);
protected:
    int posX;
    int posY;

    bool path[4];
    BoardField *neighbor[4];
    Player *playerSlot[4];
};

#endif // LBOARDFIELD_H
