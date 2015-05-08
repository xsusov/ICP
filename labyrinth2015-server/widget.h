#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    Widget(QWidget *parent, int n);
    ~Widget();

public:
    /**
     * @brief set_buttons prepares all buttons
     * @param n - size of the gameboard
     */
    void set_buttons(int n);
    /**
     * @brief set_labels prepares all labels
     * @param n - size of the gameboard
     */
    void set_labels(int n);
    void reset_scenes(int n, std::string board_str, std::string field_str);

    void change_player_info(); /// Not implemented





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
    void handle_save();
    void handle_mute();
    void handle_menu();
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

};

#endif // WIDGET_H
