#include "player.h"
#include "constants.h"
#include "deck.h"

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
