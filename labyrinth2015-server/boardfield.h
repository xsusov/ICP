#ifndef BOARDFIELD_H
#define BOARDFIELD_H

#include <iostream>
#include "gameobject.h"
#include "gameitem.h"
#include "player.h"

class BoardField : public GameObject
{
public:
    BoardField();
    BoardField(const int x, const int y );
    int getPosX();
    int getPosY();
    BoardField *getNeighbor( int direction );
    void rotate( int direction );
    bool isOpenPath( int direction );
    void draw();
    char getPath(const int direction);
    void printRow(const int row);
    char getPlayerSlot(const int pos);
    void appendRow(const int row, std::string& str);

protected:
    int posX;
    int posY;

    bool path[4];
    BoardField *neighbor[4];
    Player *playerSlot[4];
    GameItem *item;
private:
};

#endif // BOARDFIELD_H
