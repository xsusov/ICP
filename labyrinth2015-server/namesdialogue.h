#ifndef NAMESDIALOGUE_H
#define NAMESDIALOGUE_H


#include <string>
#include <QDialog>

namespace Ui {
class NamesDialogue;
}

class NamesDialogue : public QDialog
{
    Q_OBJECT

public:
    explicit NamesDialogue(QWidget *parent = 0);
    ~NamesDialogue();
    void enable_n(int n);

private slots:

    void on_player_1_textEdited(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_player_2_textEdited(const QString &arg1);

    void on_player_3_textEdited(const QString &arg1);

    void on_player_4_textEdited(const QString &arg1);

private:
    Ui::NamesDialogue *ui;
};

#endif // NAMESDIALOGUE_H
