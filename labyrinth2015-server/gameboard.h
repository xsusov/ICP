#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "exception"
#include "constants.h"
#include "boardfield.h"
#include "lboardfield.h"

class GameBoard
{
public:
    GameBoard( const int size );
    ~GameBoard();
    void draw();
    void setUpFields();
    BoardField* getField( const int posX, const int posY );
    BoardField *getNeighbour(BoardField *from, const int direction );
    inline int pos(const int x, const int y);
    inline bool isCorner(const int pos);
    bool isPathOpen(const int xFrom, const int yFrom, const int direction );
private:
    const int size;
    const int totalFields;
    BoardField **field;
};

#endif // GAMEBOARD_H
