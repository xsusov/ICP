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
    ~NamesDialogue();
    explicit NamesDialogue(QWidget *parent = 0);
    void set_ok_button(const QString &arg1);
    void enable_n(int n);
    void compare();

private slots:
    void on_player_1_textEdited(const QString &arg1);
    void on_player_2_textEdited(const QString &arg1);
    void on_player_3_textEdited(const QString &arg1);
    void on_player_4_textEdited(const QString &arg1);
    void on_cancel_button_clicked();
    void on_ok_button_clicked();


private:
    Ui::NamesDialogue *ui;
};

#endif // NAMESDIALOGUE_H
