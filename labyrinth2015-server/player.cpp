#include "player.h"
#include "constants.h"

Player::Player( const std::string playerName )
    : name{ playerName }
{
}

char Player::draw()
{
    return figure != nullptr ? figure->draw() : labyrinth::opened;
}
