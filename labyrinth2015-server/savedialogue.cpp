#include "savedialogue.h"
#include "ui_savedialogue.h"

SaveDialogue::SaveDialogue(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveDialogue)
{
    ui->setupUi(this);
}

SaveDialogue::~SaveDialogue()
{
    delete ui;
}
