#include "iboardfield.h"

IBoardField::IBoardField(const int x, const int y)
    : posX{x},
      posY{y},
      path{true, false, true, false}
{
}
