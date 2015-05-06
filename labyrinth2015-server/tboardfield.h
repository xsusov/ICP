#ifndef TBOARDFIELD_H
#define TBOARDFIELD_H

#include <iostream>
#include "boardfield.h"

class TBoardField : public BoardField
{
public:
    TBoardField(const int x,const int y, GameItem *item = nullptr);
    virtual void rotateInside( const int x, const int y, const int max );
    virtual int getLogNum();
};

#endif // TBOARDFIELD_H
