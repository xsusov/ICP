#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "player.h"
#include "controller.h"
#include "game.h"

class ClientHandler : public Controller
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
    int getShiftDirection(bool rowMode);
    int getMoveDirection();
    std::string getGame();
    Game *getNewGame();
    virtual int getShift(const int size, int &shiftNum, int &direction);

private:
    std::string userInput;
};

#endif // CLIENTHANDLER_H
