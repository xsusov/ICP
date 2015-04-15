#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <iostream>
#include "gameobject.h"

class GameItem : GameObject
{
public:
    GameItem( const char figure = '$');
    char getFigure();
private:
    char figure;
};

#endif // GAMEITEM_H
