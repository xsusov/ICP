#ifndef SAVEDIALOGUE_H
#define SAVEDIALOGUE_H

#include <QDialog>

namespace Ui {
class SaveDialogue;
}

class SaveDialogue : public QDialog
{
    Q_OBJECT

public:
    explicit SaveDialogue(QWidget *parent = 0);
    ~SaveDialogue();

private:
    Ui::SaveDialogue *ui;
};

#endif // SAVEDIALOGUE_H
