#include "menu.h"
#include "widget.h"
#include "ui_menu.h"

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


void Menu::on_quit_clicked()
{
    QApplication::quit();
}

void Menu::on_new_game_clicked()
{
    int n = 11;
    Widget *w = new Widget(0, n);

    // Do stuff.
    std::string brd = "XXXXXXXXXXXXXXXXXXXXXXXXXX@  XX   XX   XX   XX&  XX    X g    k    l      XX   XX   XX   XX   XX   XXX XXXX XXXX XXXXXXXXX XXXX XXXXXXXXXXXXXX XXXX XXX   XX   XX   XX   XX   XX   XX a       X    X   XX   XX   XX   XX   XX   XXX XXXX XXXXXXXXXXXXXX XXXX XXXXXXXXX XXXX XXXX XXX   XX   XX   XX   XX   XX c    d      XX   X  j XX   XX   XX   XX   XX   XXX XXXX XXXX XXXX XXXX XXXX XXXXXXXXX XXXX XXXX XXX   XX   XX   XX   XX   XX b    e X       h X  f XX   XX   XX   XX   XX   XXXXXXXX XXXXXXXXXXXXXX XXXX XXXX XXXX XXXX XXXX XXX   XX   XX   XX   XX   XX i                X    XX   XX   XX   XX   XX   XXXXXXXXXXXXXXXXXXXXXXXXXX";
    std::string fld = "XX XXX   XX i  X   XXXXXX";

    w->reset_scenes(n, brd, fld);
    w->set_buttons(n);
    w->set_labels(n);

    // Show game and hide menu.
    w->show();
    this->hide();
}
