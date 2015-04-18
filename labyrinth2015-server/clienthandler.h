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
};

#endif // CLIENTHANDLER_H
