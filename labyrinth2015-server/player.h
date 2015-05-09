#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>
#include <iostream>
//#include "playerfigure.h"
#include "card.h"
#include "deck.h"
#include "boardfield.h"
#include "constants.h"

// Forward declaration of BoardField class
class BoardField;

class Player
{
public:
    Player(const std::string playerName );
    Player(const std::string playerName, const char figure, const int score, Card* card = nullptr );
    void drawCard(Deck &deck);

    //Getters.
    Card * getCard() {return card;}
    int getScore() {return score;}
    int getColor() {return color;}
    char getFigure() {return figure;}
    std::string getName() {return name;}
    BoardField *getCurField() {return curField;}
    std::string getQuest();
    char getItem();

    //Setters.
    void incScore();
    void placeOnField(BoardField *newField);
    bool pickupItem();
    void dropCard() {card=nullptr;}

    /// For GUI.
    void set_color(int color) {this->color = color;}

private:
    static int count;

    int id;
    std::string name;
    int score;
    char figure;
    int color;
    Card *card;
    BoardField *curField;
};

void print_results(std::vector<Player *> &players);

#endif // PLAYER_H
