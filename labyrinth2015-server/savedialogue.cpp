#include "widget.h"
#include "savedialogue.h"
#include "ui_savedialogue.h"

#include <iostream>

SaveDialogue::SaveDialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveDialogue)
{
    ui->setupUi(this);
}

SaveDialogue::SaveDialogue(QWidget *parent, Game *ptr) :
    QDialog(parent),
    ui(new Ui::SaveDialogue)
{
    ui->setupUi(this);
    this->game_ptr = ptr;
}

SaveDialogue::~SaveDialogue()
{
    delete ui;
}

void SaveDialogue::on_lineEdit_textChanged(const QString &arg1)
{
    if (arg1.isEmpty())
        this->ui->save_button->setDisabled(true);
    else
        this->ui->save_button->setEnabled(true);
}

void SaveDialogue::on_close_button_clicked()
{
    ((Widget*)parentWidget())->enable_button("save");
    this->hide();
    delete this;
}

void SaveDialogue::on_save_button_clicked()
{
    if (this->game_ptr->saveGame(this->ui->lineEdit->displayText().toStdString()))
    {
        this->ui->message->setText("Game saved.");
    }
    else this->ui->message->setText("Error, retry.");
}
