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
    void draw();
    void setUpFields();
    BoardField& getField( const int posX, const int posY );

private:
    const int size;
    const int totalFields;
    BoardField *field;
};

#endif // GAMEBOARD_H
