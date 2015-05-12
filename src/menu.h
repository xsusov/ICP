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
    ~Menu();
    explicit Menu(QWidget *parent = 0);

    void enable_new_game_button();
    void disable_new_game_button();

private slots:
    void on_quit_clicked();
    void on_new_game_clicked();
    void on_load_game_clicked();

private:
    Ui::menu *ui;
};

#endif // MENU_H
