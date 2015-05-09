#include "gameover.h"
#include "ui_gameover.h"

GameOver::GameOver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOver)
{
    ui->setupUi(this);
}

GameOver::~GameOver()
{
    delete ui;
}

void GameOver::set_results(QString const results)
{
    this->ui->results->setText(results);
}

void GameOver::on_cancel_button_clicked()
{
    delete this;
}
