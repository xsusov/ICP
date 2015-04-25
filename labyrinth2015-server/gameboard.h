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
    void setUpPlayers(std::vector<Player*> &players);
    BoardField *getField( const int posX, const int posY ) const;
    BoardField *getNeighbour(const BoardField &from, const int direction ) const;
    inline int pos(const int x, const int y);
    inline bool isCorner(const int pos);
    bool isPathOpen(const int xFrom, const int yFrom, const int direction );
    void rotateFreeField(const int rotate);
    void shiftColumn(const int row, const bool up = false);
    void shiftRow(const int row, bool right = false);
    int getSize();
    void shift(const char shiftMode='r', const int num=0, const bool direction=false);
    bool movePlayer( Player *player, const int direction );
private:
    const int size;
    const int max;
    const int totalFields;
    std::vector<BoardField *> field;
    BoardField *freeField;

    inline bool isEdge(const int x, const int y) const;
    inline bool isEdgingDirection(const BoardField &from, const int direction ) const;
    inline static bool updateDirection( int &x, int &y, const int direction );
    static BoardField* makeRandBoardfield(const int x, const int y , const int randNum);
};

#endif // GAMEBOARD_H
