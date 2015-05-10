#ifndef WIDGET_H
#define WIDGET_H

#include <vector>
#include <fstream>

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QGraphicsScene>

#include "game.h"
#include "player.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    Widget(QWidget *parent, int n, Game *game);
    ~Widget();

public:
    /**
     * @brief set_buttons - prepares all buttons
     * @param n - size of the gameboard
     */
    void set_buttons();
    /**
     * @brief set_labels - prepares all labels
     */
    void set_labels();
    void set_log();
    void reset_scenes(std::string board_str, std::string field_str);

    void change_player_info(); /// Not implemented
    void change_player_info(Player *actual_player);
    void disable_buttons();
    void enable_buttons();

    void delete_game() {delete this->game;}

    void keyPressEvent(QKeyEvent * key_ptr);
    void move_player(int direction);
    void end_turn();
    void disable_button(const QString obj_name);
    void enable_button(const QString obj_name);
    void print_message(const QString message);
    void set_load_log();
signals:
    /**
     * @brief send_move sends information about moving row or column
     * @param position - position of row/column (2, 4, 6...)
     * @param type - row or column
     */
    void send_move(int position, char type);
    /**
     * @brief send_rotate sends information abot rotating free field
     */
    void send_rotate();

private slots:
    void handle_quit();
    void handle_new();
    void handle_load();
    void handle_save();
    void handle_rotate();
    void handle_undo();
    void handle_next_turn();
    void column_up();
    void column_down();
    void row_left();
    void row_right();

private:
    Ui::Widget *ui;
    // Scenes.
    QGraphicsScene *board_scene;
    QGraphicsScene *field_scene;
    // Buttons.
    std::vector<QPushButton*> buttons_ptr;
    // Log.
    std::ofstream log;
    // Game.
    QLabel *message_label;
    QLabel *player_name;
    QLabel *player_info;
    Game *game;
    int game_size;
};

std::string remove_newlines(std::string source);

#endif // WIDGET_H
