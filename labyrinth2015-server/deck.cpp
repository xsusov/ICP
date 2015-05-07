/**
 * @project LABYRINTH2015
 * ICP project
 * @class Deck
 * @author xsusov01
 * @email  xsusov01@stud.fit.vutbr.cz
 * @author xbandz00
 * @email  xbandz00@stud.fit.vutbr.cz
 * @file deck.cpp
 * @date 2015/05/10
 * @brief class for storing game cards
*/
#include "deck.h"

/**
 * @brief Deck::Deck constructor
 */
Deck::Deck()
{
}

/**
 * @brief Deck::Deck constructor with
 * @param vector with
 */
Deck::Deck(std::vector<GameItem*> &vector)
{
    addItems(vector);
}

/**
 * @brief Deck::~Deck destructor
 */
Deck::~Deck()
{
    for( Card *card : CardStack ){
        delete card;
    }
}

/**
 * @brief Deck::clear clears cards from deck
 */
void Deck::clear()
{
    CardStack.clear();
}

/**
 * @brief Deck::addItems fills CardStack with cards for each item in vector of game items
 * @param vector GameItems for adding to deck
 */
void Deck::addItems(std::vector<GameItem *> &vector)
{
    CardStack.reserve(vector.size());
    for(GameItem* item : vector){
        CardStack.push_back(new Card(item, item->getName()));
    }
    std::random_shuffle(vector.begin(), vector.end(), GameItem::randItem);
}

/**
 * @brief Deck::push adds single card to deck
 * @param card_ptr for new card of deck
 */
void Deck::push(Card * card_ptr)
{
    CardStack.push_back(card_ptr);
}

/**
 * @brief Deck::pop takes top card from deck and returns it
 * @return card from top of deck
 */
Card* Deck::pop()
{
    Card* ptr = CardStack.back();
    CardStack.pop_back();
    return ptr;
}
