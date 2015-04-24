#ifndef TBOARDFIELD_H
#define TBOARDFIELD_H

#include <iostream>
#include "boardfield.h"

class TBoardField : public BoardField
{
public:
    TBoardField(const int x,const int y);
    void rotateInside( const int x, const int y, const int max );
};

#endif // TBOARDFIELD_H
