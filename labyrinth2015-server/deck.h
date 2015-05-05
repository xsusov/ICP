#ifndef DECK_H
#define DECK_H

#include <vector>
#include "card.h"
#include "gameitem.h"

class Deck
{

public:
    Deck();
    Deck(std::vector<GameItem*> &vector);
    unsigned int size() {return CardStack.size();}
    void addItems(std::vector<GameItem*> &vector);
    void push(Card*);
    Card* pop();

private:
    std::vector<Card*> CardStack;
};

#endif // DECK_H
