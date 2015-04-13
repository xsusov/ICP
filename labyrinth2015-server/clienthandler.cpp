#include "clienthandler.h"

ClientHandler::ClientHandler()
{
}

bool ClientHandler::startNewGame()
{
    std::cout << "Press ENTER to start new game." << std::endl;
    char anykey = getchar();
    return anykey;
}

int ClientHandler::getSize()
{
    std::cout << "Please, select game board size: " << std::endl;
    std::cout << "In range from 5 to 11" << std::endl;
    int size;
    std::cin >> size;
    return size;
}

