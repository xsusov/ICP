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
#include <fstream>
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
    /// MVC:
    Game *game {nullptr};       /// MODEL
    ViewerCli view;             /// VIEW
    ClientHandler controller;   /// CONTROLLER
    std::ofstream log;          /// LOG


    log.open("labyrinth.log",  std::fstream::out | std::fstream::trunc );
    if( !log.is_open() ){
        std::cerr << "err opening log file" << std::endl;
    }

    view.welcome();
    std::srand(time(NULL));

    std::string gameName {""};    
    if((gameName = controller.getGame()).empty()){
        game = controller.getNewGame();
    }
    else{
        game = Game::loadGame(gameName);
    }

    if( !game ){
        return 0;
    }

    try{
        int rotate;
        int shiftNum, direction;

        game->setUp();

        do{
            /// start new round and use view to display it to player
            game->nextRound();
            view.drawHeader(game->getRoundHeader());
            view.drawBoard(game->getBoardStr());
            view.drawField(game->getFreeFieldString());

            /// free field rotation before shifiting (can be skipped)
            while((rotate = controller.getRotate()) > 0){
                game->getBoard()->rotateFreeField(rotate);
                view.drawField(game->getFreeFieldString());
            }

            /// shifting row or column of gameboard (can be skipped)
            if(controller.getShift(game->getBoard()->getSize(), shiftNum, direction)){
                game->shift(shiftNum, direction);
                view.drawBoard(game->getBoardStr());
                view.drawField(game->getFreeFieldString());
            }

            /// movement
            while((direction = controller.getMoveDirection()) != stop){
                if(!game->move(direction)){
                    view.drawHeader(game->getRoundHeader());
                    view.drawWarnning(wrongDirection);
                    continue;
                }

                view.drawBoard(game->getBoardStr());
                if( game->turnEnd()){
                    break;
                }
            }

            log << game->getRoundStr();
            log.flush();

        }while( !game->finish());

        ///print_results(game->getPlayers()); // Results.
        view.drawResults(game->getPlayers());
    }
    catch(std::exception &ex){
        std::cerr << ex.what() << std::endl;
    }

    delete game;

    return cliGame();
}

int main()
{
    /// terminal mode
    return cliGame();
}

