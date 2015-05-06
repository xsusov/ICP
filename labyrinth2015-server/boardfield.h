#ifndef BOARDFIELD_H
#define BOARDFIELD_H

#include <iostream>
#include <vector>
#include "gameobject.h"
#include "gameitem.h"
#include "player.h"
#include "constants.h"

// forward declaration of Player class
class Player;

class BoardField : public GameObject
{
public:
    BoardField();
    BoardField(const int x, const int y, bool pathNorth = false, bool pathEast = false, bool pathSouth = false, bool pathWest = false, GameItem* item = nullptr );
    virtual ~BoardField();

    /// position methods
    inline int getPosX() const {return posX;}
    inline int getPosY() const {return posY;}
    inline void setPosX( const int x ) {posX = x;}
    inline void setPosY( const int y ) {posY = y;}
    inline void updatePos( const int x, const int y ) {posX = x; posY = y;}
    inline void incPosX() {posX++;}
    inline void incPosY() {posY++;}
    inline void decPosX() {posX--;}
    inline void decPosY() {posY--;}
    void updateDirection( const int direction );

    char getPath(const int direction);
    char getPlayerSlot(const int pos);
    char drawItem();
    char getLogItem();
    GameItem *getItem() {return item;}
    void setItem(GameItem *newItem) {item = newItem;}
    void removeItem() {item = nullptr;}

    void rotate( int x = 1 );
    virtual void rotateInside( const int x, const int y, const int max ) = 0;
    virtual int getLogNum() = 0;
    bool isOpen(const int direction ) const;
    void draw();
    std::string getStr();
    void appendRow(const int row, std::string& str);

    void swapPlayers(BoardField &swapField);
    void addPlayer(Player *player);
    void removePlayer(Player *player);

protected:
    int posX;
    int posY;

    std::vector<bool> path;
    Player *playerSlot[labyrinth::maxPlayers];
    GameItem *item;

    inline void setPlayer(Player *oldPlayer, Player *newPlayer);
};

#endif // BOARDFIELD_H
