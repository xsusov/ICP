#include "iboardfield.h"
#include "constants.h"

using namespace labyrinth;

IBoardField::IBoardField(const int x, const int y)
    : BoardField(x, y, true, false, true, false)
{
}

void IBoardField::rotateInside(const int x, const int y, const int max)
{
    if(path[north] ? (!y || y == max ) : (!x || x == max))
        rotate();
}
