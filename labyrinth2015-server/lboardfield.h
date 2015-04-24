#ifndef LBOARDFIELD_H
#define LBOARDFIELD_H

#include <iostream>
#include "boardfield.h"

class LBoardField : public BoardField
{
public:
    LBoardField(const int x,const int y );
    void rotateInside( const int x, const int y, const int max );
};

#endif // LBOARDFIELD_H
