#include "lboardfield.h"

LBoardField::LBoardField(const int x, const int y)
    : posX{x},
      posY{y},
      path{true, true, false, false}
{
}
