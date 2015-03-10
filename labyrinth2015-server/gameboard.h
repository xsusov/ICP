#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "exception"
#include "constants.h"
#include "boardfield.h"

class GameBoard
{
public:
    GameBoard( int size );
    void draw();
private:
    const int size;
    BoardField *field;
};

#endif // GAMEBOARD_H
