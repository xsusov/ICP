#include "tboardfield.h"

TBoardField::TBoardField(const int x, const int y)
    : posX{x},
      posY{y},
      path{false, true, true, true}
{
}
