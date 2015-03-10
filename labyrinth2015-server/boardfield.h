#ifndef BOARDFIELD_H
#define BOARDFIELD_H

#include <iostream>
#include "gameobject.h"
#include "gameitem.h"
#include "player.h"

using namespace std;

class BoardField : GameObject
{
public:
    BoardField();
    int getPosX();
    int getPosY();
    BoardField *getNeighbor( int direction );
    void rotate( int direction );
    bool isOpenPath( int direction );


private:
    int posX;
    int posY;

    bool path[4];
    BoardField *neighbor[4];
    Player *playerSlot[4];
    GameItem *item;
};

#endif // BOARDFIELD_H
