/**
 * @project LABYRINTH2015
 * ICP project
 * @class StartDialogue
 * @author xsusov01
 * @email  xsusov01@stud.fit.vutbr.cz
 * @author xbandz00
 * @email  xbandz00@stud.fit.vutbr.cz
 * @file startdialogue.cpp
 * @date 2015/05/10
 * @brief start game widget
*/

#include "menu.h"
#include "widget.h"
#include "namesdialogue.h"
#include "startdialogue.h"
#include "ui_startdialogue.h"


#include "game.h"
#include <QObject>

/**
 * @brief StartDialogue::StartDialogue constructor
 * @param parent - parent widget
 * @param type - type of parent widget, Menu (true) or Widget (false)
 */
StartDialogue::StartDialogue(QWidget *parent, bool type) :
    QDialog(parent),
    ui(new Ui::StartDialogue)
{
    ui->setupUi(this);
    this->type = type;
    this->ui->start_button->hide();
    this->gameboard_size = 11;
    this->player_count = 4;
    this->item_count = 24;
}

/**
 * @brief StartDialogue::~StartDialogue destructor
 */
StartDialogue::~StartDialogue()
{
    delete ui;
}

/**
 * @brief StartDialogue::enable_start enables start button
 */
void StartDialogue::enable_start()
{
    this->ui->start_button->show();
}

/**
 * @brief StartDialogue::enable_confirm enables confirm button
 */
void StartDialogue::enable_confirm()
{
    this->ui->confirm_button->show();
}

/**
 * @brief StartDialogue::enable_dialogue enables sliders
 */
void StartDialogue::enable_dialogue()
{
    this->ui->item_slider->setEnabled(true);
    this->ui->size_slider->setEnabled(true);
    this->ui->player_slider->setEnabled(true);
}

/**
 * @brief StartDialogue::disable_dialogue disables sliders
 */
void StartDialogue::disable_dialogue()
{
    this->ui->item_slider->setDisabled(true);
    this->ui->size_slider->setDisabled(true);
    this->ui->player_slider->setDisabled(true);
}

/**
 * @brief StartDialogue::on_size_slider_valueChanged sets size of game
 * @param value - value paased from signal
 */
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

/**
 * @brief StartDialogue::on_player_slider_valueChanged sets number of players
 * @param value - value passed from signal
 */
void StartDialogue::on_player_slider_valueChanged(int value)
{
    this->player_count = value;
}

/**
 * @brief StartDialogue::on_item_slider_valueChanged sets number of items
 * @param value - values passed from signal
 */
void StartDialogue::on_item_slider_valueChanged(int value)
{
    if (value == 1) this->item_count = 12;
    else this->item_count = 24;
}

/**
 * @brief StartDialogue::on_cancel_button_clicked returns to parent widget and deletes itself
 */
void StartDialogue::on_cancel_button_clicked()
{
    if (this->type) ((Menu*)parentWidget())->show();
    else ((Widget*)parentWidget())->enable_button("new");

    delete this;
}

/**
 * @brief StartDialogue::on_confirm_button_clicked starts names dialogue
 */
void StartDialogue::on_confirm_button_clicked()
{
    NamesDialogue *get_names = new NamesDialogue(this);

    get_names->enable_n(this->player_count);
    get_names->setObjectName("names");
    get_names->show();
    this->ui->confirm_button->hide();
    this->disable_dialogue();
    this->hide();
}

/**
 * @brief StartDialogue::on_start_button_clicked allocates memory and starts the game
 */
void StartDialogue::on_start_button_clicked()
{
    this->hide(); // Hide start as game already started.
    Player::reset_count();
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
    game_window->set_buttons();
    game_window->set_labels();
    game_window->set_log();
    game_window->change_player_info(game->get_actual_player());

    // Start game.
    game_window->reset_scenes(remove_newlines(game->getBoardStr()),
                              remove_newlines(game->getFreeFieldString()));
    game_window->show();

    if (!this->type)
    {   // Delete old widget.
        ((Widget*)parentWidget())->delete_game();
        delete ((Widget*)parentWidget());
    }
}
