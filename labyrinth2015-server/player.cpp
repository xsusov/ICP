#include "constants.h"
#include "player.h"


Player::Player( const std::string name )
    : name{ name }
{
}

char Player::draw()
{
    return figure != nullptr ? figure->draw() : labyrinth::opened;
}
