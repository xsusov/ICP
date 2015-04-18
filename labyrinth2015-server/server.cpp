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

int main()
{
    std::cout << "Welcome to Labyrint server" << endl;
    //std::cout << labyrinth::welcome;

    ClientHandler *client = new ClientHandler();

    while( !client->startNewGame() );

    GameBoard *newBoard;
    while( !newBoard ){
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

    int itemCount = 3;

    newBoard->setUpFields();

    std::vector<GameItem*> items;
    GameItem::fillVector(items, itemCount);
    newBoard->setUpItems(items);
    newBoard->draw();

    return 0;
}

