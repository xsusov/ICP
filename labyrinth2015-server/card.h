#ifndef CARD_H
#define CARD_H

#include <iostream>
#include "gameitem.h"

using namespace std;

class Card
{
public:
    Card();
private:
    int id;
    string text;
    GameItem *item;
};

#endif // CARD_H
