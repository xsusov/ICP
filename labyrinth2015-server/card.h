#ifndef CARD_H
#define CARD_H

#include <iostream>
#include "gameitem.h"

class Card
{
public:
    Card(GameItem * ptr, std::string message);
    const std::string getText() {return text;}
    GameItem *getItem() {return item;}
private:
    GameItem *item;
    const std::string text;
};

#endif // CARD_H
