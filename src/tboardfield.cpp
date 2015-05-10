#include "tboardfield.h"
#include "constants.h"

using  namespace labyrinth;

TBoardField::TBoardField(const int x, const int y, GameItem *item)
    : BoardField(x, y, false, true, true, true, item)
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

int TBoardField::getLogNum()
{
    if(path[north]){
        if(path[west] && path[east]){
            return 8;
        }
        else if(path[west] && path[south]){
            return 7;
        }
        else{
            return 9;
        }
    }
    else{
        return 6;
    }
}
