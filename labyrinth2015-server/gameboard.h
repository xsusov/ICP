#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "exception"
#include "boardfield.h"
#include "lboardfield.h"
#include "tboardfield.h"
#include "iboardfield.h"

class GameBoard
{
public:
    GameBoard( const int size );
    ~GameBoard();
    void draw();
    void setUpFields();
    void setUpItems(std::vector<GameItem *> &items);
    BoardField* getField( const int posX, const int posY );
    BoardField *getNeighbour(BoardField *from, const int direction );
    inline int pos(const int x, const int y);
    inline bool isCorner(const int pos);
    bool isPathOpen(const int xFrom, const int yFrom, const int direction );
    void rotateFreeField(const int rotate);
    void shiftColumn(const int row, bool bottomToTop = false);
    void shiftRow(const int row, bool rightToLeft = false);
    int getSize();
    void shift(const char shiftMode='r', const int num=0, const bool direction=false);
private:
    const int size;
    const int totalFields;
    BoardField **field;
    BoardField *freeField;
};

#endif // GAMEBOARD_H
