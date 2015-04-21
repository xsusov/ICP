#include "player.h"
#include "constants.h"
#include "deck.h"
#include "algorithm"
int Player::count = 0;

Player::Player( const std::string playerName )
    : name{ playerName },
      score { 0 },
      figure { labyrinth::playerFigure[count++] }
{
}

void Player::drawCard(Deck &deck)
{
    card = deck.pop();
}

void Player::incScore()
{
    score++;
}

void Player::placeOnField(BoardField *newField)
{
    curField = newField;
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
