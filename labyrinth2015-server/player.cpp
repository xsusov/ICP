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

void print_results(std::vector<Player*> players)
{
    std::sort(players.begin(), players.end());
    for (int i = players.size(); i > 0; i--)
    {
        std::cout << "l";
    }
}
