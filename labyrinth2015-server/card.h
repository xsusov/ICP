#ifndef CARD_H
#define CARD_H

#include <iostream>
#include "gameitem.h"

class Card
{
public:
    Card(GameItem * ptr, std::string message);
    const std::string getText() {return text;}
private:
    GameItem *item;
    std::string text;
};

#endif // CARD_H
