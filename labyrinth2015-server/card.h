#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include "gameitem.h"

class Card
{
public:
    Card(GameItem * ptr, const std::string message);
    ~Card();
    const std::string getText() {return text;}
    GameItem *getItem() {return item;}
private:
    GameItem *item;
    const std::string text;
};

#endif // CARD_H
