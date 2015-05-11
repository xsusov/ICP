/**
 * @project LABYRINTH2015
 * ICP project
 * @class Player
 * @author xsusov01
 * @email  xsusov01@stud.fit.vutbr.cz
 * @author xbandz00
 * @email  xbandz00@stud.fit.vutbr.cz
 * @file player.cpp
 * @date 2015/05/10
 * @brief class for player's game representation
*/
#include "player.h"

int Player::count = 0;

Player::Player( const std::string playerName )
    : name{ playerName },
      score { 0 },
      figure { labyrinth::playerFigure[count++] },
      card{nullptr}
{
}

Player::Player( const std::string playerName, const char figure, const int score, Card* card )
    : name{ playerName },
      score { score },
      figure { figure },
      card {card}
{
}

void Player::drawCard(Deck &deck)
{
    card = deck.pop();
}

std::string Player::getQuest()
{
    return ((card != nullptr ) ? card->getText() : "");
}

void Player::incScore()
{
    score++;
}

void Player::placeOnField(BoardField *newField)
{
    curField = newField;
}

bool Player::pickupItem()
{
    if(curField == nullptr || card == nullptr)
        return false;

    if(curField->getItem() == card->getItem()){
        curField->removeItem();
        incScore();
        return true;
    }

    return false;
}

char Player::getItem()
{
    return (card != nullptr ) ? card->getItem()->getFigure()  : '0';
}

bool myCompare(Player * i, Player * j)
{
    return (i->getScore() < j->getScore());
}

void print_results(std::vector<Player*> &players)
{
    std::sort(players.begin(), players.end(), myCompare);
    std::cout << std::endl << "Game Over!" << std::endl;
    for (int i = players.size(); i > 0; i--)
    {
        std::cout << players[i-1]->getName() << "'s score is " << players[i-1]->getScore() << std::endl;
    }
}
