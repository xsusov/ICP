#include "gameitem.h"
#include "constants.h"
#include <random>
#include <algorithm>

GameItem::GameItem(const char figure, const std::string name)
    : figure{figure},
      name{name}
{
}

char GameItem::getFigure()
{
    return figure;
}

void GameItem::fillVector(std::vector<GameItem*> &vector, const int itemCount)
{
    for( int i = 0; i < itemCount; i++){
        vector.push_back(new GameItem(labyrinth::itemFigure[i], labyrinth::itemNames[i]));
    }

    std::random_shuffle(vector.begin(), vector.end(), GameItem::randItem);
}

int GameItem::randItem(const int itemCount)
{
    return std::rand() % itemCount;
}

void GameItem::draw()
{
    std::cout << figure;
}
