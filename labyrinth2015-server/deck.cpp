#include "deck.h"
#include <vector>
#include <random>
#include <algorithm>
#include "card.h"
#include "gameitem.h"

Deck::Deck()
{

}

Deck::~Deck()
{
    for( Card *card : CardStack ){
        delete card;
    }
}

void Deck::clear()
{
    CardStack.clear();
}

Deck::Deck(std::vector<GameItem*> &vector)
{
    addItems(vector);
}

void Deck::addItems(std::vector<GameItem *> &vector)
{
    for (GameItem* item : vector)
    {
        CardStack.push_back(new Card(item, item->getName()));
    }
    std::random_shuffle(vector.begin(), vector.end(), GameItem::randItem);
}

void Deck::push(Card * card_ptr)
{
    CardStack.push_back(card_ptr);
}

Card* Deck::pop()
{
    Card* ptr = CardStack.back();
    CardStack.pop_back();
    return ptr;
}
