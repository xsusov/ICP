#ifndef CARD_H
#define CARD_H

#include <iostream>
#include "gameitem.h"

class Card
{
public:
    Card();
private:
    int id;
    std::string text;
    GameItem *item;
};

#endif // CARD_H