/**
 * @project LABYRINTH2015
 * ICP project
 * @class IBoardField
 * @author xsusov01
 * @email  xsusov01@stud.fit.vutbr.cz
 * @author xbandz00
 * @email  xbandz00@stud.fit.vutbr.cz
 * @file iboardfield.cpp
 * @date 2015/05/10
 * @brief subclass of Boardfields type I
*/
#include "iboardfield.h"
#include "constants.h"

using namespace labyrinth;

IBoardField::IBoardField(const int x, const int y, GameItem *item)
    : BoardField(x, y, true, false, true, false, item)
{
}

void IBoardField::rotateInside(const int x, const int y, const int max)
{
    if(path[north] ? (!y || y == max ) : (!x || x == max))
        rotate();
}

int IBoardField::getLogNum()
{
    return path[north] ? 0 : 1;
}
