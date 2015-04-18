#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H
#include <iostream>
#include <string>
#include <sstream>

class ClientHandler
{
public:
    ClientHandler();
    bool startNewGame();
    int getSize();
    int getItemCount();
    int getRotate();
    char getShiftMode();
    int getShiftNum(const int size);
    bool getShiftDirection();

private:
    std::string userInput;
    std::stringstream inputStream;
};

#endif // CLIENTHANDLER_H
