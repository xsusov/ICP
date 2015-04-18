#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "playerfigure.h"
#include "card.h"
#include "deck.h"

class Player
{
public:
    Player(const std::string playerName );
    void drawCard(Deck &deck);
    //Getters.
    Card * getCard() {return card;}
    int getScore() {return score;}
    int getColor() {return color;}
    int getFigure() {return figure;}
    std::string getName() {return name;}
    //Setters.
    void incScore();

private:
    static int count;

    int id;
    std::string name;
    int score;
    char figure;
    int color;
    Card *card;
};

#endif // PLAYER_H
