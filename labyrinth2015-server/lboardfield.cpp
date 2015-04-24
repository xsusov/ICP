#include "lboardfield.h"
#include "constants.h"

using namespace labyrinth;

LBoardField::LBoardField(const int x, const int y)
    : BoardField(x, y, true, true, false, false)
{
}

void LBoardField::rotateInside(const int x, const int y, const int max)
{
    while((path[north] ? !y : y == max) || (path[east] ? x == max : !x))
        rotate();
}
