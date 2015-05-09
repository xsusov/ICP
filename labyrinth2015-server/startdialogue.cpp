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
    this->ui->start_button->setDisabled(true);
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
    this->ui->start_button->setEnabled(true);
}

void StartDialogue::enable_confirm()
{
    this->ui->confirm_button->setEnabled(true);
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

void StartDialogue::on_cancel_button_clicked()
{
    ((Menu*)parentWidget())->show();
    delete this;
}

void StartDialogue::on_confirm_button_clicked()
{
    NamesDialogue *get_names = new NamesDialogue(this);

    get_names->enable_n(this->player_count);
    get_names->setObjectName("names");
    get_names->show();
    this->ui->confirm_button->setDisabled(true);
    this->disable_dialogue();
    this->hide();
}

void StartDialogue::on_start_button_clicked()
{
    this->hide(); // Hide start as game alfready started.

    Game * game = new Game(this->gameboard_size, this->player_count, this->item_count);
    // Add players and setup.
    game->addPlayer(this->player_1);
    game->addPlayer(this->player_2);
    if (this->player_count > 2) game->addPlayer(this->player_3);
    if (this->player_count > 3) game->addPlayer(this->player_4);
    game->setUp();
    game->nextRound();

    // Prepare game main window.
    Widget* game_window = new Widget(0, this->gameboard_size, game);
    game_window->set_buttons(this->gameboard_size);
    game_window->set_labels(this->gameboard_size);
    game_window->set_log();
    game_window->change_player_info(game->get_actual_player());

    // Start game.
    game_window->reset_scenes(remove_newlines(game->getBoardStr()),
                              remove_newlines(game->getFreeFieldString()));
    game_window->show();
}
