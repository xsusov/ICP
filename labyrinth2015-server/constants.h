#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>

namespace labyrinth {

    enum direction{ north,
                    east,
                    south,
                    west,
                    stop};
    const int saveN = 6;
    const int undoN = 7;
    const int directionCount = 4;

    inline int roundDirection( const int direction ){
        return direction % directionCount;
    }

    inline int opositeDirection( const int direction ){
        return (direction + 2) % directionCount;
    }

    const int boardMinSize = 5, boardMaxSize = 11;
    const int posFree = -1;

    const int minRow = 0, maxRow = 4;
    const int minPlayers = 2, maxPlayers = 4;

    const char opened = ' ';
    const char closed = 'X';

    const int itemsSmall = 12;
    const int itemsLarge = 24;

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

    const char row = 'r';
    const std::string rowStr = "row";
    const std::string columnStr = "column";

    inline const std::string getShiftStr(const char mode){
        return (mode == row ? rowStr : columnStr);
    }

    const std::string newGame = "";
    const std::string logfile = "labyrinth.log";
    const std::string tmplogfile = "labyrinth.log.tmp";
}

#endif // CONSTANTS_H
