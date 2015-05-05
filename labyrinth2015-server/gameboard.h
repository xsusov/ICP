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
    GameBoard( const int size = 7 );
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
    int getSize() {return size;}
    void shift(const int num=0, const int direction=0);
    void shift(const int first, const int last, const int offset, const int direction, const int lastX, const int lastY );
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
    bool isWalkable(BoardField *from, const int direction ) const;
};

#endif // GAMEBOARD_H
