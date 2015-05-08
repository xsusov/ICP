#ifndef MENU_H
#define MENU_H

#include <QWidget>

namespace Ui {
class menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

private slots:
    void on_quit_clicked();

    void on_new_game_clicked();

private:
    Ui::menu *ui;
};

#endif // MENU_H