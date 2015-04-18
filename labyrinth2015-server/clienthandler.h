#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H
#include <iostream>

class ClientHandler
{
public:
    ClientHandler();
    bool startNewGame();
    int getSize();
    int getItemCount();
    int getRotate();
};

#endif // CLIENTHANDLER_H
