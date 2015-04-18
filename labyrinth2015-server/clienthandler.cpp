#include <iostream>
#include <sstream>
#include "clienthandler.h"
#include <stdio.h>

ClientHandler::ClientHandler()
    : userInput{""},
      inputStream{userInput}
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

int ClientHandler::getItemCount()
{
    int count;
    std::cout << "Select number of items: " << std::endl << "12 or 24" << std::endl;
    std::cin >> userInput;
    std::stringstream numberStream(userInput);
    if( !(numberStream >> count)){
        std::cout << "Invalid number, press Q to Quit, or ANY KEY to try again";
        char anykey;
        std::cin >> anykey;
        if( anykey == 'q' || anykey == 'Q' )
            return -1;
        else
            return getItemCount();
    }

    if( count != 12 && count != 24 ){
        return getItemCount();
    }

    return count;
}

int ClientHandler::getRotate()
{
    int rotate;
    std::cout << "How many times do you wanna rotate free field for: " << std::endl;
    std::cin >> userInput;
    std::stringstream numberStream(userInput);
    if( !(numberStream >> rotate)){
        std::cout << "Invalid number, press ANY KEY to try again";
        return getRotate();
    }
    return rotate;
}
