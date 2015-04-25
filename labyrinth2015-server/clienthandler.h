#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "player.h"

class ClientHandler
{
public:
    ClientHandler();
    bool startNewGame();
    int getSize();
    int getItemCount();
    std::string getPlayerName(const std::vector<Player *> &players);
    int getPlayerCount();
    int getRotate();
    char getShiftMode();
    int getShiftNum(const int size, char mode);
    bool getShiftDirection(bool rowMode);

private:
    std::string userInput;
};

#endif // CLIENTHANDLER_H
