#include "menu.h"
#include "widget.h"
#include "ui_menu.h"
#include "startdialogue.h"

#include <iostream>
#include <QApplication>

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::enable_new_game_button()
{
    this->ui->new_game->setEnabled(true);
}

void Menu::disable_new_game_button()
{
    this->ui->new_game->setDisabled(true);
}

void Menu::on_quit_clicked()
{
    QApplication::quit();
}

void Menu::on_new_game_clicked()
{
    StartDialogue * new_game_dialogue = new StartDialogue(this);
    this->hide();
    new_game_dialogue->show();
}
