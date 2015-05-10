/**
 * @project LABYRINTH2015
 * ICP project
 * @class Card
 * @author xsusov01
 * @email  xsusov01@stud.fit.vutbr.cz
 * @author xbandz00
 * @email  xbandz00@stud.fit.vutbr.cz
 * @file boardfield.cpp
 * @date 2015/05/10
 * @brief class for card of items for players quests
*/
#include "card.h"

/**
 * @brief Card::Card constructor
 * @param ptr_item item player with card needs to find
 * @param message  flavour text of quest
 */
Card::Card(GameItem * ptr_item, const std::string message)
    : item{ptr_item},
      text{message}
{
}

/**
 * @brief Card::~Card destructor
 */
Card::~Card()
{

}
