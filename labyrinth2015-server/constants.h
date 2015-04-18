#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>

namespace labyrinth {
    const int north = 0, east = 1, south = 2, west = 3;

    inline int opositeDirection( const int direction ){
        return (direction + 2) % 4;
    }

    const int boardMinSize = 5, boardMaxSize = 11;

    const char opened = ' ';
    const char closed = 'X';

    const char playerFigure[4]{ '@', '&', '%', '!'};
    const char itemFigure[24]{'a', 'b', 'c', 'd', 'e', 'f',
                              'g', 'h', 'i', 'j', 'k', 'l',
                              'm', 'n', 'o', 'p', 'q', 's',
                              't', 'u', 'v', 'w', 'x', 'y'};
    const std::string itemNames[24]
                              {"a", "b", "c", "d", "e", "f",
                               "g", "h", "i", "j", "k", "l",
                               "m", "n", "o", "p", "q", "s",
                               "t", "u", "v", "w", "x", "y"};

    const std::string welcome = {
"********************************************************************************\n"
"******************************   LABYRINTH   ***********************************\n"
"********************************************************************************\n"};
}

#endif // CONSTANTS_H
