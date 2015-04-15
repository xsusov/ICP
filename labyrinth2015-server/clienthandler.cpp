#include <iostream>
#include <sstream>
#include "clienthandler.h"

ClientHandler::ClientHandler()
{
}

bool ClientHandler::startNewGame()
{
    std::cout << "Press ANY KEY to start new game." << std::endl;
    char anykey = getchar();
    return anykey;
}

int ClientHandler::getSize()
{
    std::cout << "Please, select game board size: " << std::endl;
    std::cout << "Eneter odd number in range from 5 to 11." << std::endl;
    int size ;
    std::string userInput;
    getline(std::cin, userInput);
    std::stringstream numberStream(userInput);
    if( !(numberStream >> size) ){
        std::cout << "Invalid number, press Q to Quit, or ANY KEY to try again";
        char anykey;
        std::cin >> anykey;

        if( anykey == 'q' || anykey == 'Q' )
            return -1;
        else
            return getSize();
    }

    return size;
}

