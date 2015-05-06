#include "card.h"
#include <string>

Card::Card(GameItem * ptr_item, const std::string message)
    : item{ptr_item},
      text{message}
{
}
