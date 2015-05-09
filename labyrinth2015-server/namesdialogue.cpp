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

void NamesDialogue::set_ok_button(const QString &arg1)
{
    if (arg1.isEmpty())
    {
        this->ui->ok_button->setDisabled(true);
        return;
    }
    else
        this->ui->ok_button->setEnabled(true);

    for (auto sign: arg1)
    {
        if (sign.isLetterOrNumber()) continue;
        else
        {
            this->ui->ok_button->setDisabled(true);
            return;
        }
    }
    this->ui->ok_button->setEnabled(true);
}

void NamesDialogue::on_player_1_textEdited(const QString &arg1)
{
    set_ok_button(arg1);
}

void NamesDialogue::on_player_2_textEdited(const QString &arg1)
{
   set_ok_button(arg1);
}

void NamesDialogue::on_player_3_textEdited(const QString &arg1)
{
   set_ok_button(arg1);
}

void NamesDialogue::on_player_4_textEdited(const QString &arg1)
{
    set_ok_button(arg1);
}

void NamesDialogue::on_ok_button_clicked()
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

void NamesDialogue::on_cancel_button_clicked()
{
    ((StartDialogue*)parentWidget())->enable_dialogue();
    ((StartDialogue*)parentWidget())->enable_confirm();
    ((StartDialogue*)parentWidget())->show();
    delete this;
}
