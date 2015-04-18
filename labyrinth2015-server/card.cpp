#include "card.h"
#include <string>

Card::Card(GameItem * ptr, std::string message)
{
    item = ptr;
    text = message;
}
