#ifndef TBOARDFIELD_H
#define TBOARDFIELD_H

#include <iostream>
#include "boardfield.h"

class TBoardField : public BoardField
{
public:
    TBoardField(const int x,const int y);
protected:
    int posX;
    int posY;

    bool path[4];
    BoardField *neighbor[4];
    Player *playerSlot[4];
};

#endif // TBOARDFIELD_H
