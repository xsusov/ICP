#include "menu.h"
#include "widget.h"
#include "namesdialogue.h"
#include "startdialogue.h"
#include "ui_startdialogue.h"

/// Game files and classes:
#include "game.h"

#include <iostream>
#include <QObject>

StartDialogue::StartDialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialogue)
{
    ui->setupUi(this);
    this->ui->pushButton->setDisabled(true);
    this->gameboard_size = 11;
    this->player_count = 4;
    this->item_count = 24;
}

StartDialogue::~StartDialogue()
{
    delete ui;
}

void StartDialogue::enable_start()
{
    this->ui->pushButton->setEnabled(true);
}

void StartDialogue::enable_dialogue()
{
    this->ui->item_slider->setEnabled(true);
    this->ui->size_slider->setEnabled(true);
    this->ui->player_slider->setEnabled(true);
}

void StartDialogue::disable_dialogue()
{
    this->ui->item_slider->setDisabled(true);
    this->ui->size_slider->setDisabled(true);
    this->ui->player_slider->setDisabled(true);
}


void StartDialogue::on_size_slider_valueChanged(int value)
{
    switch (value)
    {
        case 5: this->gameboard_size = 5; break;
        case 6: this->gameboard_size = 7; break;
        case 7: this->gameboard_size = 9; break;
        case 8: this->gameboard_size = 11; break;
    }
}

void StartDialogue::on_player_slider_valueChanged(int value)
{
    this->player_count = value;
}

void StartDialogue::on_item_slider_valueChanged(int value)
{
    if (value == 1) this->item_count = 12;
    else this->item_count = 24;
}


//Cancel button
void StartDialogue::on_pushButton_2_clicked()
{
    ((Menu*)parentWidget())->show();
    delete this;
}

// Set names button.
void StartDialogue::on_pushButton_3_clicked()
{
    NamesDialogue *get_names = new NamesDialogue(this);

    get_names->enable_n(this->player_count);
    get_names->setObjectName("names");
    get_names->show();
    this->ui->pushButton_3->setDisabled(true);
    this->disable_dialogue();
    this->hide();
}

// Start game.
void StartDialogue::on_pushButton_clicked()
{
    this->hide(); // Hide start as game alfready started.

    Game * game = new Game(this->gameboard_size, this->player_count, this->item_count);
    // Add players and setup.
    game->addPlayer(this->player_1, 1);
    game->addPlayer(this->player_2, 2);
    game->addPlayer(this->player_3, 3);
    game->addPlayer(this->player_4, 4);
    game->setUp();
    game->nextRound();

    // Prepare game main window.
    Widget* game_window = new Widget(0, this->gameboard_size, game);
    game_window->set_buttons(this->gameboard_size);
    game_window->set_labels(this->gameboard_size);
    game_window->set_log();
    game_window->change_player_info(game->get_actual_player());

    // Start game.
    game_window->reset_scenes(this->gameboard_size,
                              remove_newlines(game->getBoardStr()),
                              remove_newlines(game->getFreeFieldString()));
    game_window->show();


/*
     * int cliGame()
{
    /// MVC:
    Game *game {nullptr};       /// MODEL
    ViewerCli view;             /// VIEW
    ClientHandler controller;   /// CONTROLLER


    /// opens log for logging in progress of game
    std::ofstream log;          /// LOG
    log.open(logfile,  std::fstream::out | std::fstream::trunc );
    if( !log.is_open() ){
        std::cerr << errLogOpen << std::endl;
    }

    view.welcome();             /// welcome message from our game to players
    std::string gameName {""};  /// get Game from MainMenu
    try{
        if((gameName = controller.getGame()).empty()){  /// New Game
            game = controller.getNewGame();
            game->setUp();
            game->nextRound();
        }
        else{   /// or load Game from savegame file
            game = Game::loadGame(gameName);
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

        /// log statrt state of game
        log << game->getRoundStr();
        log.flush();

        while( true ){
            /// start new round and use view to display it to player
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

            /// movement until players passing turn to next player
            while((direction = controller.getMoveDirection()) != stop){
                if(direction == saveN){   /// player wants to save game instead of movement
                    gameName = controller.getSaveGameName();
                    game->saveGame(gameName);
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

            if( game->finish()){ /// game ends when one player reaches final score
                break;
            }

            game->nextRound();
            /// log state of game in this turn
            log << game->getRoundStr();
            log.flush();
        }

        ///prints result of game
        view.drawResults(game->getPlayers());
    }
    catch(std::exception &ex){
        std::cerr << ex.what() << std::endl;
    }

    delete game;    /// clean
    return 0;       /// returns to MainMenu
}*/
}
