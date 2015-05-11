/**
 * @project LABYRINTH2015
 * ICP project
 * @class GameOver
 * @author xsusov01
 * @email  xsusov01@stud.fit.vutbr.cz
 * @author xbandz00
 * @email  xbandz00@stud.fit.vutbr.cz
 * @file gameover.cpp
 * @date 2015/05/10
 * @brief game over pop up window
*/

#include "gameover.h"
#include "ui_gameover.h"

/**
 * @brief GameOver::GameOver game over pop up window constructor
 * @param parent - parent widget (game window)
 */
GameOver::GameOver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOver)
{
    ui->setupUi(this);
}

/**
 * @brief GameOver::~GameOver game over pop up window destructor
 */
GameOver::~GameOver()
{
    delete ui;
}

/**
 * @brief GameOver::set_results prints results to label
 * @param results - results converted to Qstring
 */
void GameOver::set_results(QString const results)
{
    this->ui->results->clear();
    this->ui->results->setText(results);
}

/**
 * @brief GameOver::on_cancel_button_clicked hides this window
 */
void GameOver::on_cancel_button_clicked()
{
    delete this;
}
