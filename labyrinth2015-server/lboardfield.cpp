#include "lboardfield.h"
#include "constants.h"

using namespace labyrinth;

LBoardField::LBoardField(const int x, const int y, GameItem *item)
    : BoardField(x, y, true, true, false, false, item)
{
}

void LBoardField::rotateInside(const int x, const int y, const int max)
{
    while((path[north] ? !y : y == max) || (path[east] ? x == max : !x))
        rotate();
}

int LBoardField::getLogNum()
{
    if(path[north]){
        return path[west] ? 5 : 2;
    }
    return path[west] ? 4 : 3;
}
