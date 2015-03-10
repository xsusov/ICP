#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "playerfigure.h"
#include "card.h"

using namespace std;

class Player
{
public:
    Player();
private:
    int id;
    string name;
    int score;
    PlayerFigure *figure;
    int color;
    Card *currentCard;
};

#endif // PLAYER_H
