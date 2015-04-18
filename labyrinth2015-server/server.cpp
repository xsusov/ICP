/**
 * @project: LABYRINT 2015
 * ICP project
 * @author: xsusov01, xband00
 * @file: server.c
 * @date: 2.3.2015
 * @brief: server side of labyrint application
*/

/// TDD - test first, enjoyment from pure coding later

using namespace std;

#include <iostream>
#include <exception>
/// Classes:
#include "constants.h"
#include "clienthandler.h"
#include "player.h"
#include "gameboard.h"
#include "gameitem.h"
#include <random>
#include <ctime>

int main()
{
    std::srand(time(NULL));
    std::cout << "Welcome to Labyrint server" << endl;
    std::cout << labyrinth::welcome;

    ClientHandler *client = new ClientHandler();

    while( !client->startNewGame() );

    GameBoard *newBoard = nullptr;
    while( newBoard == nullptr ){
        try{
            int size = client->getSize();
            if( size == -1 )
                return 1;

            newBoard = new GameBoard( size );
        }
        catch( const char *exp ){
            std::cout << exp << endl;
        }
    }

    int itemCount = 0;
    while( !itemCount ){
        try{
            itemCount = client->getItemCount();
        }
        catch( const char *exp ){
            std::cout << exp << endl;
        }
    }

    newBoard->setUpFields();

    std::vector<GameItem*> items;
    GameItem::fillVector(items, itemCount);

    newBoard->setUpItems(items);
    bool win = false;
    while( !win ){
        newBoard->draw();
        int rotate = client->getRotate();
        if( rotate > 0)
            newBoard->rotateFreeField( rotate );

        newBoard->draw();

        char shiftMode = client->getShiftMode();
        if(!(shiftMode == 'r' || shiftMode == 'c'))
            continue;
        else{
            int num = client->getShiftNum(newBoard->getSize(), shiftMode);
            bool direction = client->getShiftDirection(shiftMode);
            newBoard->shift(shiftMode, num, direction);
        }
        newBoard->draw();
    }


    return 0;
}

