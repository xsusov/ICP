/**
 * @project LABYRINTH2015
 * ICP project
 * @class GameItem
 * @author xsusov01
 * @email  xsusov01@stud.fit.vutbr.cz
 * @author xbandz00
 * @email  xbandz00@stud.fit.vutbr.cz
 * @file gameitem.cpp
 * @date 2015/05/10
 * @brief class representing game item placed on boardfield and searched by players
*/
#include "gameitem.h"
#include "constants.h"
#include <random>
#include <algorithm>

/**
 * @brief GameItem::GameItem constructor
 * @param figure
 * @param name
 */
GameItem::GameItem(const char figure, const std::string name)
    : figure{figure},
      name{name}
{
}

/**
 * @brief GameItem::~GameItem destructor
 */
GameItem::~GameItem()
{

}

/**
 * @brief GameItem::fillVector fills vector with newly created items
 * @param vector    - reference to vector for storing items
 * @param itemCount - number of items to be created
 */
void GameItem::fillVector(std::vector<GameItem*> &vector, const int itemCount)
{
    for( int i = 0; i < itemCount; i++){
        vector.push_back(new GameItem(labyrinth::itemFigure[i], labyrinth::itemNames[i]));
    }

    std::random_shuffle(vector.begin(), vector.end(), GameItem::randItem);
}

/**
 * @brief GameItem::randItem returns random number of avialible items
 * @param itemCount - max range for item number
 * @return random item number
 */
int GameItem::randItem(const int itemCount)
{
    return std::rand() % itemCount;
}

/**
 * @brief GameItem::draw prints item's figure to standard output
 */
void GameItem::draw()
{
    std::cout << figure;
}
