#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "playerfigure.h"
#include "card.h"

class Player
{
public:
    Player(const std::string name );
    char draw();
private:
    int id;
    std::string name;
    int score;
    PlayerFigure *figure;
    int color;
    Card *currentCard;
};

#endif // PLAYER_H
