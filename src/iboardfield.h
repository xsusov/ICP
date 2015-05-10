#ifndef IBOARDFIELD_H
#define IBOARDFIELD_H

#include <iostream>
#include "boardfield.h"

class IBoardField : public BoardField
{
public:
    IBoardField(const int x,const int y, GameItem *item = nullptr);
    virtual void rotateInside( const int x, const int y, const int max );
    virtual int getLogNum();
};

#endif // IBOARDFIELD_H
