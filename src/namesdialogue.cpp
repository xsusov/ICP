/**
 * @project LABYRINTH2015
 * ICP project
 * @class NamesDialogue
 * @class NamesDialogue
 * @author xsusov01
 * @email  xsusov01@stud.fit.vutbr.cz
 * @author xbandz00
 * @email  xbandz00@stud.fit.vutbr.cz
 * @file namesdialogue.cpp
 * @date 2015/05/10
 * @brief get names dialogue
*/

#include "namesdialogue.h"
#include "startdialogue.h"
#include "ui_namesdialogue.h"

/**
 * @brief NamesDialogue::NamesDialogue constructor
 * @param parent - parent widget (StartDialogue)
 */
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

/**
 * @brief NamesDialogue::~NamesDialogue destructor
 */
NamesDialogue::~NamesDialogue()
{
    delete ui;
}

/**
 * @brief NamesDialogue::enable_n enables n player
 * @param n - number of players to enable (int: 1, 2, 3, 4)
 */
void NamesDialogue::enable_n(int n)
{
    if (n > 2) ui->player_3->setEnabled(true);
    if (n > 3) ui->player_4->setEnabled(true);
}

/**
 * @brief NamesDialogue::set_ok_button disables "OK button" in case of invalid name
 * @param arg1 - QString from edit line
 */
void NamesDialogue::set_ok_button(const QString &arg1)
{
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

/**
 * @brief NamesDialogue::compare checks names for duplicates or empty names
 */
void NamesDialogue::compare()
{
        if (this->ui->player_1->displayText() == this->ui->player_2->displayText())
            this->ui->ok_button->setDisabled(true);
        if (this->ui->player_1->displayText() == this->ui->player_3->displayText())
            this->ui->ok_button->setDisabled(true);
        if (this->ui->player_1->displayText() == this->ui->player_4->displayText())
            this->ui->ok_button->setDisabled(true);
        //
        if (this->ui->player_2->displayText() == this->ui->player_3->displayText())
            this->ui->ok_button->setDisabled(true);
        if (this->ui->player_2->displayText() == this->ui->player_4->displayText())
            this->ui->ok_button->setDisabled(true);
        //
        if (this->ui->player_3->displayText() == this->ui->player_4->displayText())
            this->ui->ok_button->setDisabled(true);

        if (this->ui->player_1->displayText().isEmpty() ||
            this->ui->player_2->displayText().isEmpty() ||
            this->ui->player_3->displayText().isEmpty() ||
            this->ui->player_4->displayText().isEmpty())
        {
            this->ui->ok_button->setDisabled(true);
            return;
        }
}

/**
 * @brief NamesDialogue::on_player_1_textEdited calls above functions when input line for player 1 is edited
 * @param arg1 - QString from edit line
 */
void NamesDialogue::on_player_1_textEdited(const QString &arg1)
{
    this->set_ok_button(arg1);
    this->compare();
}

/**
 * @brief NamesDialogue::on_player_1_textEdited calls above functions when input line for player 2 is edited
 * @param arg1 - QString from edit line
 */
void NamesDialogue::on_player_2_textEdited(const QString &arg1)
{
    this->set_ok_button(arg1);
    this->compare();
}

/**
 * @brief NamesDialogue::on_player_1_textEdited calls above functions when input line for player 3 is edited
 * @param arg1 - QString from edit line
 */
void NamesDialogue::on_player_3_textEdited(const QString &arg1)
{
    this->set_ok_button(arg1);
    this->compare();
}

/**
 * @brief NamesDialogue::on_player_1_textEdited calls above functions when input line for player 4 is edited
 * @param arg1 - QString from edit line
 */
void NamesDialogue::on_player_4_textEdited(const QString &arg1)
{
    this->set_ok_button(arg1);
    this->compare();
}

/**
 * @brief NamesDialogue::on_ok_button_clicked sends names backt to parent and deletes itself
 */
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

/**
 * @brief NamesDialogue::on_cancel_button_clicked returns to parent widget and deletes itself
 */
void NamesDialogue::on_cancel_button_clicked()
{
    ((StartDialogue*)parentWidget())->enable_dialogue();
    ((StartDialogue*)parentWidget())->enable_confirm();
    ((StartDialogue*)parentWidget())->show();
    delete this;
}
