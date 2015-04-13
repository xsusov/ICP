#ifndef PLAYERFIGURE_H
#define PLAYERFIGURE_H

#include <iostream>
#include "gameobject.h"

class PlayerFigure : GameObject
{
public:
    PlayerFigure();
    char draw();
private:
    char figure;
};

#endif // PLAYERFIGURE_H
