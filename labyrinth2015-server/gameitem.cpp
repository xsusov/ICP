#include "gameitem.h"

GameItem::GameItem(const char figure)
    : figure{figure}
{
}

char GameItem::getFigure()
{
    return figure;
}
