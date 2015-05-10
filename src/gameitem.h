#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <iostream>
#include "gameobject.h"
#include <vector>

class GameItem : GameObject
{
public:
    GameItem(const char figure = '$', const std::string name = "item");
    ~GameItem();
    char getFigure();
    static void fillVector(std::vector<GameItem *> &vector, const int itemCount);
    static int randItem(const int itemCount);

    std::string getName() {return name;}
    void draw();
private:
    char figure;
    std::string name;
};

#endif // GAMEITEM_H
