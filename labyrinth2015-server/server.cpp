/**
 * @project: LABYRINT 2015
 * ICP project
 * @author: xsusov01, xbandz00
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
#include "strings.h"
#include "clienthandler.h"
#include "player.h"
#include "gameboard.h"
#include "gameitem.h"
#include "deck.h"
#include <random>
#include <ctime>

using namespace labyrinth;

int main()
{
    /*
     MVC - model - viewer - controler
     CMD vs. GUI -> zmena (idealne) 2 radky v main labyrinth-cli.cpp a labyrinth.cpp

     kernel = new Kernel(); //

     controler = new CmdControler();
     viewer = new CmdViewer();
     game = controler->getGame()
     Kernel->run( game, viewer, controler )
     */

    std::srand(time(NULL));
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

/*
    while (true)
    {
        std::cout << client->getMoveDirection() << std::endl;
    }
*/

    int itemCount = 0;
    while( !itemCount ){
        try{
            itemCount = client->getItemCount();
        }
        catch( const char *exp ){
            std::cout << exp << endl;
        }
    }

    int playerCount = 0;
    while( !playerCount ){
        try{
            playerCount = client->getPlayerCount();
        }
        catch( const char *exp ){
            std::cout << exp << endl;
        }
    }

    int actualPlayer = 0;
    Player* player = nullptr;
    std::vector<Player*> players;
    for (int i = 0; i < playerCount; i++){
        std::cout << strPlayerNumber << i+1 << std::endl;
        players.push_back(new Player(client->getPlayerName(players)));
    }

    newBoard->setUpFields();
    newBoard->setUpPlayers(players);

    std::vector<GameItem*> items;
    GameItem::fillVector(items, itemCount);

    newBoard->setUpItems(items);

    Deck deck(items);

    bool win = false;
    const int winningScore = itemCount/playerCount;
    while( !win ){
        player = players[actualPlayer++ % playerCount];

        std::cout << strRound << actualPlayer << " " << player->getName()+ strTurn << std::endl;
        if( player->getCard() == nullptr ){
            player->drawCard(deck);
        }
        std::cout << "Quest: " << player->getQuest() << std::endl;
        newBoard->draw();
        int rotate = client->getRotate();
        if( rotate > 0)
            newBoard->rotateFreeField( rotate );

        newBoard->draw();
        char shiftMode = client->getShiftMode();
        if(!(shiftMode == 'r' || shiftMode == 'c')){

        }
        else{
            int num = client->getShiftNum(newBoard->getSize(), shiftMode);
            bool direction = client->getShiftDirection(shiftMode == 'r');
            newBoard->shift(shiftMode, num, direction);
        }
        newBoard->draw();

        int dir = client->getMoveDirection();
        while(dir != stop)
        {

            std::cout << dir << std::endl;
            if( !newBoard->movePlayer(player, dir)){
                std::cout << "cant move in choosen direction" << std::endl;
            }
            if(player->pickupItem()){
                newBoard->draw();
                break;
            }
            newBoard->draw();
            dir = client->getMoveDirection();
        }

        if(player->getScore() == winningScore)
            win = true;
    }
    print_results(players); // Results.
    return 0;
}

