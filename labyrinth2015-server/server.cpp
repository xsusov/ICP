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
#include "game.h"
#include "controller.h"
#include "viewer.h"
#include "viewercli.h"

using namespace labyrinth;


int cliGame()
{
    int size {0};
    int itemCount {0};
    int playerCount {0};
    std::string gameName {""};
    /// MVC
    /// MODEL
    Game *game {nullptr};
    /// VIEW
    ViewerCli view;
    /// CONTROLLER
    ClientHandler controller;


    /// controler->getGame();
    if((gameName = controller.getGame()).empty()){
        size = controller.getSize();
        itemCount = controller.getItemCount();
        playerCount = controller.getPlayerCount();
        game = new Game(size, playerCount, itemCount);

        for(int i = 0; i < playerCount; i++){
            game->addPlayer(controller.getPlayerName(game->getPlayers()));
        }
    }
    else{
        game = Game::loadGame(gameName);
    }

    try{
        int rotate;
        int shiftNum, direction;
        do{
            /// start new round and use view to display it to player
            game->nextRound();
            view.drawHeader(game->getRoundHeader());
            view.drawBoard(game->getBoardStr());

            /// free field rotation before shifiting (can be skipped)
            while((rotate = controller.getRotate()) > 0){
                game->getBoard()->rotateFreeField(rotate);
                view.drawField(game->getFreeFieldString());
            }

            /// shifting row or column of gameboard (can be skipped)
            if(controller.getShift(size, shiftNum, direction)){
                game->shift(shiftNum, direction);
                view.drawBoard(game->getBoardStr());
            }

            /// movement
            while((direction = controller.getMoveDirection()) != stop){
                if(!game->move(direction)){
                    view.drawWarnning(wrongDirection);
                    continue;
                }

                view.drawBoard(game->getBoardStr());
                if( game->turnEnd()){
                    break;
                }
            }

        }while( !game->finish());

        ///view.drawResult();
    }
    catch(std::exception &ex){
        std::cerr << ex.what() << std::endl;
    }

    delete game;

    return 0;
}

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

    /// terminal mode
    ///return cliGame();



    ClientHandler *client = new ClientHandler();

    while( !client->startNewGame() );

    int size;

    GameBoard *newBoard = nullptr;
    while( newBoard == nullptr ){
        try{
            size = client->getSize();
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
    Deck discardpile;

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
            int direction = client->getShiftDirection(shiftMode == 'r');
            newBoard->shift(num, direction);
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
                discardpile.push(player->getCard());
                player->dropCard();
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

