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

int main()
{
    cout << "Welcome to Labyrint server" << endl;

    ClientHandler *client = new ClientHandler();

    while( !client->startNewGame() );

    GameBoard *newBoard;
    try{
        newBoard = new GameBoard( client->getSize() );
    }
    catch( const char *exp ){
        std::cout << "caught " << exp << endl;
    }

    newBoard->draw();

    return 0;
}

