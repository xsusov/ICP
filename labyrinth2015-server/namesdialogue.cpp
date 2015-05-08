#
#include "namesdialogue.h"
#include "startdialogue.h"
#include "ui_namesdialogue.h"

NamesDialogue::NamesDialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NamesDialogue)
{
    ui->setupUi(this);
    ui->player_1->setEnabled(true);
    ui->player_2->setEnabled(true);
    ui->player_3->setDisabled(true);
    ui->player_4->setDisabled(true);
}

NamesDialogue::~NamesDialogue()
{
    delete ui;
}

void NamesDialogue::enable_n(int n)
{
    if (n > 2) ui->player_3->setEnabled(true);
    if (n > 3) ui->player_4->setEnabled(true);
}

void NamesDialogue::on_player_1_textEdited(const QString &arg1)
{
    for (auto sign: arg1)
    {
        if (sign.isLetterOrNumber()) continue;
        else
        {
            this->ui->pushButton_2->setDisabled(true);
            return;
        }
    }
    this->ui->pushButton_2->setEnabled(true);
}

void NamesDialogue::on_player_2_textEdited(const QString &arg1)
{
    for (auto sign: arg1)
    {
        if (sign.isLetterOrNumber()) continue;
        else
        {
            this->ui->pushButton_2->setDisabled(true);
            return;
        }
    }
    this->ui->pushButton_2->setEnabled(true);
}

void NamesDialogue::on_player_3_textEdited(const QString &arg1)
{
    for (auto sign: arg1)
    {
        if (sign.isLetterOrNumber()) continue;
        else
        {
            this->ui->pushButton_2->setDisabled(true);
            return;
        }
    }
    this->ui->pushButton_2->setEnabled(true);
}

void NamesDialogue::on_player_4_textEdited(const QString &arg1)
{
    for (auto sign: arg1)
    {
        if (sign.isLetterOrNumber()) continue;
        else
        {
            this->ui->pushButton_2->setDisabled(true);
            return;
        }
    }
    this->ui->pushButton_2->setEnabled(true);
}

void NamesDialogue::on_pushButton_clicked()
{
    ((StartDialogue*)parentWidget())->show();
    delete this;
}

void NamesDialogue::on_pushButton_2_clicked()
{
    // Takes strings from edit fields, converts them to std::string and returns to parent.
    ((StartDialogue*)parentWidget())->set_player_1(this->ui->player_1->displayText().toStdString());
    ((StartDialogue*)parentWidget())->set_player_2(this->ui->player_2->displayText().toStdString());
    ((StartDialogue*)parentWidget())->set_player_3(this->ui->player_3->displayText().toStdString());
    ((StartDialogue*)parentWidget())->set_player_4(this->ui->player_4->displayText().toStdString());
    // Enable start and return.
    ((StartDialogue*)parentWidget())->enable_start();
    ((StartDialogue*)parentWidget())->show();
    delete this;
}
