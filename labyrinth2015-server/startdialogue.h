#ifndef STARTDIALOGUE_H
#define STARTDIALOGUE_H

#include <string>
#include <QDialog>

namespace Ui {
class StartDialogue;
}

class StartDialogue : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialogue(QWidget *parent = 0);
    ~StartDialogue();
    void enable_start();

    void set_player_1(std::string name) {this->player_1 = name;}
    void set_player_2(std::string name) {this->player_2 = name;}
    void set_player_3(std::string name) {this->player_3 = name;}
    void set_player_4(std::string name) {this->player_4 = name;}

private slots:

    void on_size_slider_valueChanged(int value);

    void on_player_slider_valueChanged(int value);

    void on_item_slider_valueChanged(int value);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::StartDialogue *ui;

    int item_count;
    int player_count;
    int gameboard_size;

    std::string player_1;
    std::string player_2;
    std::string player_3;
    std::string player_4;
};

#endif // STARTDIALOGUE_H
