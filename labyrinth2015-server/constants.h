#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace labyrinth {
    const int north = 0, east = 1, south = 2, west = 3;

    inline int opositeDirection( const int direction ){
        return (direction + 2) % 4;
    }

    const int boardMinSize = 5, boardMaxSize = 11;

    const char opened = ' ';
    const char closed = '#';

    const char playerFigure[4]{ '@', '&', '%', '!'};
/*
    const char *welcome =
"********************************************************************************\n"
"******************************   LABYRINTH   ***********************************\n"
"********************************************************************************\n"
;*/
}

#endif // CONSTANTS_H
