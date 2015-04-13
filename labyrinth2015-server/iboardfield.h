#ifndef IBOARDFIELD_H
#define IBOARDFIELD_H

#include <iostream>
#include "boardfield.h"

class IBoardField : public BoardField
{
public:
    IBoardField(const int x,const int y);
protected:
    int posX;
    int posY;

    bool path[4];
    BoardField *neighbor[4];
    Player *playerSlot[4];
};

#endif // IBOARDFIELD_H
