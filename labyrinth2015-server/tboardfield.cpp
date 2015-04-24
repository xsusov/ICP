#include "tboardfield.h"
#include "constants.h"

using  namespace labyrinth;

TBoardField::TBoardField(const int x, const int y)
    : BoardField(x, y, false, true, true, true)
{
}

void TBoardField::rotateInside(const int x, const int y, const int max)
{
    while(( !x && path[west])
        ||( !y && path[north])
        ||( x == max && path[east])
        ||( y == max && path[south]))
        rotate();
}
