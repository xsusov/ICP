#include "gameitem.h"
#include "constants.h"
#include <random>
#include <algorithm>

GameItem::GameItem(const char figure)
    : figure{figure}
{
}

char GameItem::getFigure()
{
    return figure;
}

void GameItem::fillVector(std::vector<GameItem*> &vector, const int itemCount)
{
    for( int i = 0; i < itemCount; i++){
        GameItem *newItem = new GameItem(labyrinth::itemFigure[i]);
        vector.push_back(newItem);
    }

    std::random_shuffle(vector.begin(), vector.end(), GameItem::randItem);
}

int GameItem::randItem(const int itemCount)
{
    return std::rand() % itemCount;
}
