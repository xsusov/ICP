#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <iostream>
#include "gameobject.h"
#include <vector>

class GameItem : GameObject
{
public:
    GameItem( const char figure = '$');
    char getFigure();
    static void fillVector(std::vector<GameItem *> &vector, const int itemCount);
    static int randItem(const int itemCount);
private:
    char figure;
};

#endif // GAMEITEM_H
