#ifndef BOARDFIELD_H
#define BOARDFIELD_H

#include <iostream>
#include <vector>
#include "gameobject.h"
#include "gameitem.h"
#include "player.h"

class BoardField : public GameObject
{
public:
    BoardField();
    BoardField(const int x, const int y, bool pathNorth = false, bool pathEast = false, bool pathSouth = false, bool pathWest = false, GameItem* item = nullptr );
    int getPosX();
    int getPosY();
    BoardField *getNeighbor( int direction );
    void rotate( int x );
    bool isOpen( int direction );
    void draw();
    char getPath(const int direction);
    void printRow(const int row);
    char getPlayerSlot(const int pos);
    char getItem();
    void appendRow(const int row, std::string& str);
protected:
    int posX;
    int posY;

    std::vector<bool> path;
    BoardField *neighbor[4];
    Player *playerSlot[4];
    GameItem *item;
private:
};

#endif // BOARDFIELD_H
