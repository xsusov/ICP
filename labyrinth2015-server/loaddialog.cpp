#include "loaddialog.h"
#include "ui_loaddialog.h"

#include "menu.h"
#include "game.h"
#include "widget.h"

LoadDialog::LoadDialog(QWidget *parent, bool type) :
    QDialog(parent),
    ui(new Ui::LoadDialog)
{
    ui->setupUi(this);
    this->type = type;
}

LoadDialog::~LoadDialog()
{
    delete ui;
}

void LoadDialog::on_lineEdit_textEdited(const QString &arg1)
{
    if (arg1.isEmpty())
        this->ui->load_button->setDisabled(true);
    else
        this->ui->load_button->setEnabled(true);
}

void LoadDialog::on_close_button_clicked()
{
    if (this->type) ((Menu*)parentWidget())->show();
    else ((Widget*)parentWidget())->enable_button("load");

    delete this;
}

void LoadDialog::on_load_button_clicked()
{
    this->hide(); // Hide start as game alfready started adn load game
    Game *game = nullptr;
    try
    {
        game = Game::loadGame(this->ui->lineEdit->displayText().toStdString());
        if (game == nullptr) throw(1);
    }
    catch (...)
    {
        this->ui->message->setText("An error occurred.");
        this->show();
        return;
    }

    // Prepare game main window.
    Widget* game_window = new Widget(0, game->get_game_size(), game);
    game_window->set_buttons();
    game_window->set_labels();
    game_window->set_log();
    game_window->change_player_info(game->get_actual_player());

    // Start game.
    game_window->reset_scenes(remove_newlines(game->getBoardStr()),
                              remove_newlines(game->getFreeFieldString()));
    game_window->show();

    if (!this->type)
    {   // Delete old game.
        delete ((Widget*)parentWidget());
    }
}
