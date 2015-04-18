#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "playerfigure.h"
#include "card.h"

class Player
{
public:
    Player(const std::string playerName );
    char draw();
private:
    int id;
    std::string name;
    int score;
    PlayerFigure *figure;
    int color;
    Card *card;
};

#endif // PLAYER_H
