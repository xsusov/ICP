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
    void setPosX( const int x );
    void setPosY( const int y );
    void incPosX();
    void incPosY();
    void decPosX();
    void decPosY();
    void updatePos( const int x, const int y );
    BoardField *getNeighbor( int direction );
    void rotate( int x );
    //virtual void rotateIn( const int x, const int y, const int size ) = 0;
    bool isOpen( int direction );
    void draw();
    char getPath(const int direction);
    void printRow(const int row);
    char getPlayerSlot(const int pos);
    char drawItem();
    void appendRow(const int row, std::string& str);
    void setItem(GameItem *newItem);
    GameItem *getItem();
    void swapPlayers(BoardField &swapField);
    void addPlayer(Player *player);
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
