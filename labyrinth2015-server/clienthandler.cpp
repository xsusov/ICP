#include <iostream>
#include <sstream>
#include "clienthandler.h"
#include <string>
#include <stdio.h>
#include "player.h"
#include "constants.h"
#include "strings.h"
#include <limits>

using namespace labyrinth;

ClientHandler::ClientHandler()
    : userInput{""}
{
}

bool ClientHandler::startNewGame()
{
    std::cout << strAnyKey << std::endl;
    return getchar();
}

int ClientHandler::getSize()
{
    std::cout << strBoardSize << std::endl << strBoardSizeRange << std::endl;
    int size ;
    std::cin.clear();
    fflush(stdin);

    do{
    std::cin >> userInput;
    std::stringstream numberStream(userInput);

        if( !(numberStream >> size) ){
            std::cout << strInvalidNumber << std::endl;
            char anykey;
            std::cin >> anykey;
            if( anykey == 'q' || anykey == 'Q' ){
                return -1;
            }
            std::cout << strBoardSize << std::endl << strBoardSizeRange << std::endl;
        }
        else if( size < labyrinth::boardMinSize || size > labyrinth::boardMaxSize ){
            std::cout << expWrongSize << std::endl;
        }
        else if( !(size%2) ){
            std::cout << expWrongEvenSize << std::endl;
        }
        else{
            break;
        }
    } while(1);

    return size;
}

int ClientHandler::getItemCount()
{
    int count;
    std::cout << strItemsNumber << std::endl;
    std::cin >> userInput;
    std::stringstream numberStream(userInput);
    if( !(numberStream >> count)){
        std::cout << strInvalidNumber;
        char anykey;
        std::cin >> anykey;
        if( anykey == 'q' || anykey == 'Q' ){
            return -1;
        }
        else{
            return getItemCount();
        }
    }

    if( !(count == itemsSmall || count == itemsLarge )){
        return getItemCount();
    }

    return count;
}

int ClientHandler::getRotate()
{
    int rotate;
    std::cout << strRotateNumber << std::endl;
    std::cin >> userInput;
    std::stringstream numberStream(userInput);
    if( !(numberStream >> rotate)){
        std::cout << strInvalidNumber;
        return getRotate();
    }
    return rotate;
}

char ClientHandler::getShiftMode()
{
    char mode;
    std::cout << strShiftMode << std::endl;
    std::cin >> mode;
    return mode;
}

int ClientHandler::getShiftNum(const int size, char mode)
{
    int num;
    std::cout << strShiftChoosePre << getShiftStr(mode) << strShiftChoosePost << std::endl;
    std::cout << 2 << "-" << size - 1 << std::endl;
    std::cin >> userInput;
    std::stringstream numberStream(userInput);
    if( !(numberStream >> num)){
        std::cout << "wrong " << getShiftStr(mode) << strTryAgain << std::endl;
        return getShiftNum(size, mode);
    }
    if( num < 1 || num > size || num % 2){
        std::cout << "wrong " << getShiftStr(mode) << strTryAgain << std::endl;
        return getShiftNum(size, mode);
    }

    return num - 1;
}

int ClientHandler::getShiftDirection(bool rowMode)
{
    int direction;
    std::cout << strSelectDirection << std::endl
              << "0 - " << (rowMode ? "right" : "up") << std::endl
              << "1 - " << (rowMode ? "left" : "down") << std::endl;
    std::cin >> direction;

    direction *= 2;
    if( rowMode )
        direction++;

    return direction;
}

int ClientHandler::getPlayerCount()
{
    int count;
    std::cout << strSelectPlayerNum << std::endl;
    std::cin >> userInput;
    std::stringstream numberStream(userInput);
    if( !(numberStream >> count)){
        std::cout << strInvalidNumber;
        char anykey;
        std::cin >> anykey;
        if( anykey == 'q' || anykey == 'Q' ){
            return -1;
        }
        else{
            return getPlayerCount();
        }
    }

    if( count < minPlayers || count > maxPlayers) {
        std::cout << strNumOORange << std::endl;
        return getPlayerCount();
    }
   std::getline(std::cin, userInput);
   return count;
}

std::string ClientHandler::getPlayerName(const std::vector<Player *> &players)
{
    std::string name = "";
    std::cout << strChooseName << std::endl;
    std::getline(std::cin, name);
    if(name.empty())
        return getPlayerName(players);

    for (Player * player : players){
        if (player->getName() == name){
            std::cout << strUniqueName << std::endl;
            return getPlayerName(players);
        }
    }
    return name;
}

int ClientHandler::getMoveDirection()
{
    char direction = 0;
    std::cout << strSelectMoveDirection << std::endl;
    std::cin >> direction;
    if (direction == 'W' || direction == 'w') return north;
    else if (direction == 'S' || direction == 's') return south;
    else if (direction == 'A' || direction == 'a') return west;
    else if (direction == 'D' || direction == 'd') return east;
    else if (direction == 'E' || direction == 'e' || direction == '0' ) return stop;

    std::cout << strInvalidMove << std::endl;
    return getMoveDirection();
}

int ClientHandler::mainMenu()
{
    int option;

    std::cout << strMenuNew << std::endl
              << strMenuLoad << std::endl
              << strMenuCredits << std::endl
              << strMenuExit << std::endl;

    std::cin.clear();
    std::cin >> option;
    return option;
}



std::string ClientHandler::getGame()
{
    std::string savegame {newGame};
    switch( mainMenu() ){
        case 1:
            return newGame;
        case 2:
            std::cout << strLoadGame << std::endl;
            std::cin >> savegame;
            return savegame;
        case 3:
            std::cout << strCredits << std::endl;
            return getGame();
        case 4:
            exit(0);
    }

    return newGame;
}

Game *ClientHandler::getNewGame()
{
    Game *newGame {nullptr};
    int size {0};
    int itemCount {0};
    int playerCount {0};

    size = getSize();
    if(size < 0){
        return nullptr;
    }
    itemCount = getItemCount();
    if(itemCount < 0){
        return nullptr;
    }
    playerCount = getPlayerCount();
    if(playerCount < 0){
        return nullptr;
    }

    newGame = new Game(size, playerCount, itemCount);

    for(int i = 0; i < playerCount; i++){
        newGame->addPlayer(getPlayerName(newGame->getPlayers()));
    }

    return newGame;
}

int ClientHandler::getShift(const int size, int &shiftNum, int &direction)
{
    char mode = getShiftMode();
    if(!( mode == 'r' || mode == 'R' || mode == 'c' || mode == 'C' ))
        return 0;
    shiftNum = getShiftNum(size, mode);
    direction = getShiftDirection(mode == row);
    return 1;
}
