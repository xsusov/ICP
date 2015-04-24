#ifndef IBOARDFIELD_H
#define IBOARDFIELD_H

#include <iostream>
#include "boardfield.h"

class IBoardField : public BoardField
{
public:
    IBoardField(const int x,const int y);
    void rotateInside( const int x, const int y, const int max );
};

#endif // IBOARDFIELD_H
