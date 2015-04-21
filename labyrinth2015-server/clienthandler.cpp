#include <iostream>
#include <sstream>
#include "clienthandler.h"
#include <string>
#include <stdio.h>
#include "player.h"

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

char ClientHandler::getShiftMode()
{
    char mode;
    std::cout << "Select shift mode:" << std::endl << "r - rows shift" << std::endl << "c - columns shift" << std::endl << "other - skip" << std::endl;
    std::cin >> mode;
    return mode;
}

int ClientHandler::getShiftNum(const int size, char mode)
{
    int num;
    std::cout << "Which "<< (mode == 'r' ? "row" : "column") << " do you want to shif (only even): " << std::endl;
    std::cout << "1-" << size << std::endl;
    std::cin >> userInput;
    std::stringstream numberStream(userInput);
    if( !(numberStream >> num)){
        std::cout << "wrong " << (mode == 'r' ? "row" : "column") << " number, try again" << std::endl;
        return getShiftNum(size, mode);
    }
    if( num < 1 || num > size || num % 2){
        std::cout << "wrong " << (mode == 'r' ? "row" : "column") << " number, try again" << std::endl;
        return getShiftNum(size, mode);
    }

    return num - 1;
}

bool ClientHandler::getShiftDirection(bool rowMode)
{
    int direction;
    std::cout << "Select shift direction: " << std::endl
              << "0 - " << (rowMode ? "right" : "down") << std::endl
              << "1 - " << (rowMode ? "left" : "up") << std::endl;
    std::cin >> direction;
    return direction;
}

int ClientHandler::getPlayerCount()
{
    int count;
    std::cout << "Select number of players: " << std::endl << "2, 3 or 4" << std::endl;
    std::cin >> userInput;
    std::stringstream numberStream(userInput);
    if( !(numberStream >> count)){
        std::cout << "Invalid number, press Q to Quit, or ANY OTHER KEY to try again";
        char anykey;
        std::cin >> anykey;
        if( anykey == 'q' || anykey == 'Q' )
            return -1;
        else
            return getPlayerCount();
    }

    if( count < 2  || count > 4) {
        std::cout << "Number out of range." << std::endl;
        return getPlayerCount();
    }
   std::getline(std::cin, userInput);
   return count;
}

std::string ClientHandler::getPlayerName(std::vector<Player *> players)
{
    std::string name = "";
    std::cout << "Choose your name." << std::endl;
    std::getline(std::cin, name);
    for (Player * player : players)
    {
        if (player->getName() == name)
        {
            std::cout << "Player name has to be unique." << std::endl;
            return getPlayerName(players);
        }
    }
    return name;
}
