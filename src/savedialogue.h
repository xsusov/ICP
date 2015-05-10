#ifndef SAVEDIALOGUE_H
#define SAVEDIALOGUE_H

#include <QDialog>

#include "game.h"

namespace Ui {
class SaveDialogue;
}

class SaveDialogue : public QDialog
{
    Q_OBJECT

public:
    explicit SaveDialogue(QWidget *parent = 0);
    SaveDialogue(QWidget *parent, Game *ptr);
    ~SaveDialogue();


private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_close_button_clicked();

    void on_save_button_clicked();

private:
    Ui::SaveDialogue *ui;
    Game *game_ptr;
};

#endif // SAVEDIALOGUE_H
