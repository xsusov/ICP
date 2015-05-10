/**
 * @project LABYRINTH2015
 * ICP project
 * @author xsusov01
 * @email  xsusov01@stud.fit.vutbr.cz
 * @author xbandz00
 * @email  xbandz00@stud.fit.vutbr.cz
 * @file server.cpp
 * @date 2015/05/10
 * @brief main module of labryinth-cli
*/
/// TDD - test first, enjoyment from pure coding later (jk)
/// standard libraries
#include <iostream>
#include <fstream>
#include <exception>
#include <random>
#include <ctime>
/// Classes:
#include "constants.h"
#include "strings.h"
#include "clienthandler.h"
#include "player.h"
#include "gameboard.h"
#include "gameitem.h"
#include "deck.h"
#include "game.h"
#include "controller.h"
#include "viewer.h"
#include "viewercli.h"

using namespace labyrinth;

/**
 * @brief cliGame
 *        implements model view controller interface for running game,
 *        displaying it (on cout in Cli mode) and recieving user input (from cin in Cli mode)
 * @return default itself in recursion, or exit by user or by error
 */
int cliGame()
{
    /// MVC:
    Game *game {nullptr};       /// MODEL
    ViewerCli view;             /// VIEW
    ClientHandler controller;   /// CONTROLLER
    bool loaded = false;
    std::srand(time(NULL));     /// srand for 'random' numbers generation seed
    view.welcome();             /// welcome message from our game to players
    std::string gameName {""};  /// get Game from MainMenu
    bool undo = false;
    /// opens log for logging in progress of game
    std::ofstream log;          /// LOG
    try{
        if((gameName = controller.getGame()).empty()){  /// New Game
            game = controller.getNewGame();
            game->setUp();
            game->nextRound();
            /// log statrt state of game
            log.open(logfile,  std::fstream::out | std::fstream::trunc );
            if( !log.is_open() ){
                std::cerr << errLogOpen << std::endl;
            }
        }
        else{   /// or load Game from savegame file
            game = Game::loadGame(gameName);
            loaded = true;
            log.open(logfile, std::fstream::out | std::ios::app );
            ///std::cout << log.tellp() ;
            if( !log.is_open() ){
                std::cerr << errLogOpen << std::endl;
            }
        }
    }
    catch(std::exception &ex){
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    if( !game ){
        return 1;
    }

    try{
        int rotate, shiftNum, direction;
        while( true ){
            /// start new round and use view to display it to player
            view.drawHeader(game->getRoundHeader());
            view.drawBoard(game->getBoardStr());
            view.drawField(game->getFreeFieldString());
            if( !loaded ){
                if( !undo ){
                    log << game->getRoundStr();
                    log.flush();
                }
                else{
                    undo = false;
                }
                /// free field rotation before shifiting (can be skipped)
                while((rotate = controller.getRotate()) > 0){
                    game->getBoard()->rotateFreeField(rotate);
                    view.drawField(game->getFreeFieldString());
                }

                /// shifting row or column of gameboard (can be skipped)
                if(controller.getShift(game->getBoard()->getSize(), shiftNum, direction)){
                    while( !game->shift(shiftNum, direction) ){ /// check that player don't reverse last turn by shifting
                        view.drawWarnning(strWrongShift);
                        controller.getShift(game->getBoard()->getSize(), shiftNum, direction);
                    }

                    view.drawBoard(game->getBoardStr());
                    view.drawField(game->getFreeFieldString());
                }
            }
            else{
                loaded = false;
            }

            /// movement until players passing turn to next player
            while((direction = controller.getMoveDirection()) != stop){
                if(direction == saveN){   /// player wants to save game instead of movement
                    gameName = controller.getSaveGameName();
                    game->saveGame(gameName);
                }
                else if(direction == undoN ){
                    if( !game->isUndoPossible() ){
                        view.drawWarnning(strWrongUndo);
                        continue;
                    }
                    else{
                        log.close();
                        if( game->undo() ){
                            delete game;
                            game = Game::loadGame(tmplogfile);
                            ///game->setRound(game->getRound() - 1);
                            std::remove(tmplogfile.c_str());
                            log.open(logfile,  std::fstream::out | std::ios::app );
                            if( !log.is_open() ){
                                std::cerr << errLogOpen << std::endl;
                            }
                            loaded = true;
                            undo = true;
                            break;
                        }
                        log.open(logfile,  std::fstream::out | std::ios::app );
                        if( !log.is_open() ){
                            std::cerr << errLogOpen << std::endl;
                        }
                    }
                }
                else if(!game->move(direction)){    /// movement in direction given by user wasn't possible
                    view.drawHeader(game->getRoundHeader());
                    view.drawWarnning(wrongDirection);
                    continue;
                }

                /// displays GameBoard after move
                view.drawBoard(game->getBoardStr());
                if( game->turnEnd()){   /// turn ends when player picks up item
                    break;
                }
            }

            if(loaded){
                loaded = false;
                continue;
            }

            if( game->finish()){ /// game ends when one player reaches final score
                break;
            }

            /// log state of game in this turn
            game->nextRound();
        }

        ///prints result of game
        view.drawResults(game->getPlayers());
    }
    catch(std::exception &ex){
        std::cerr << ex.what() << std::endl;
    }

    delete game;    /// clean
    return 0;       /// returns to MainMenu
}

/**
 * @brief main function of labyrinth-cli
 * @return exit by user or by catching error
 */
int main()
{
    int ret;
    while((ret = cliGame()) == 0);
    /// terminal mode
    return ret;
}

