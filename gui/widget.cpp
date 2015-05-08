#include "widget.h"
#include "ui_widget.h"
#include "pixmap_ops.h"
#include "field_const.h"

#include <iostream>

#include <QGraphicsPixmapItem>
#include <QApplication>
#include <QPushButton>
#include <QObject>
#include <QLabel>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::Widget(QWidget *parent, int n) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    board_scene = new QGraphicsScene;
    field_scene = new QGraphicsScene;

    this->setFixedWidth(n * 50 + 350);
    this->setFixedHeight(n * 50 + 150);

    ui->setupUi(this);
    // Add scenes.
    ui->view_1->setScene(board_scene);
    ui->view_2->setScene(field_scene);
    // Set views fixed size.
    ui->view_1->setFixedWidth(n * 50 + 350);
    ui->view_1->setFixedHeight(n * 50 + 150);
    ui->view_2->setFixedWidth(n * 50 + 350);
    ui->view_2->setFixedHeight(n * 50 + 150);
    // Set background color: transparent.
    ui->view_1->setStyleSheet("background: transparent");
    ui->view_2->setStyleSheet("background: transparent");
}

/**
 * @brief Widget::~Widget - widget destructor.
 */
Widget::~Widget()
{
    delete ui;
}

/**
 * @brief Widget::reset_scenes (re)sets the scenes
 * @param board - pointer to pixmap conating gameboard
 * @param field - pointer po pixmap conating free field
 * @param card - pointer to pixmap containg card
 */
void Widget::reset_scenes(int n, std::string board_str, std::string field_str)
{
    const char **board_ptr = to_pixmap(n, board_str);
    const char **field_ptr = to_pixmap(1, field_str);

    QPixmap *board = new QPixmap(board_ptr);
    QPixmap *field = new QPixmap(field_ptr);
    QPixmap *card = new QPixmap(no_card);

    // Set board scene.
    this->board_scene->clear();
    this->board_scene->addPixmap(*board);

    // Set field scene.
    this->field_scene->clear();
    this->field_scene->addPixmap(*field);
    this->field_scene->setSceneRect(n/2 * 50 + 150, -130, 60, 60);
    // Add card.
    QGraphicsPixmapItem *card_ptr = this->field_scene->addPixmap(*card);
    card_ptr->setPos(0, -220);

    // Delete pixmaps.
    delete board;
    delete field;
    delete card;
}

/**
 * @brief Widget::set_buttons prepares all buttons used in widget
 * @param n - size of a boardfield.
 */
void Widget::set_buttons(int n)
{
    // All magical constants here were carefully chossen by a professional (lol).
    // It is scientifically proven that these constants are good for your health.
    // Changing them will cause cancer.

    // Buttons count.
    int button_half = n - 1;

    // Rotate button.
    QPushButton *rotate_free_field = new QPushButton(this);
    rotate_free_field->setText("Rotate");
    rotate_free_field->setObjectName("rotate");
    rotate_free_field->move(this->width()/2 - n * 25 - 80, this->height()/2 + 102);
    rotate_free_field->setMaximumSize(60, 25);
    QObject::connect(rotate_free_field, SIGNAL (clicked()), this, SLOT (handle_rotate()));

    // Undo button. (Under rotate button).
    QPushButton *undo = new QPushButton(this);
    undo->setText("Undo");
    undo->setObjectName("undo");
    undo->move(this->width()/2 - n * 25 - 80, this->height()/2 + 132);
    undo->setMaximumSize(60, 25);
    QObject::connect(undo, SIGNAL (clicked()), this, SLOT (handle_undo()));

    // Next turn button. (Under rotate field scene and buttons).
    QPushButton *next_turn = new QPushButton(this);
    next_turn->setText("Next Turn");
    next_turn->setObjectName("next_turn");
    next_turn->move(this->width()/2 - n * 25 - 150, this->height()/2 + 165);
    next_turn->setMaximumSize(120, 25);
    next_turn->setMinimumSize(120, 25);
    QObject::connect(next_turn, SIGNAL (clicked()), this, SLOT (handle_next_turn()));

    // Main menu button. (Part of "menu").
    QPushButton *menu = new QPushButton(this);
    menu->setText("Main\nMenu");
    menu->setObjectName("menu");
    menu->move(this->width() - 100, this->height()/2 - 115);
    menu->setMaximumSize(70, 50);
    menu->setMinimumSize(70, 50);
    QObject::connect(menu, SIGNAL (clicked()), this, SLOT (handle_menu()));

    // Save button. (Part of "menu").
    QPushButton *save = new QPushButton(this);
    save->setText("Save");
    save->setObjectName("save");
    save->move(this->width() - 100, this->height()/2 - 55);
    save->setMaximumSize(70, 50);
    save->setMinimumSize(70, 50);
    QObject::connect(save, SIGNAL (clicked()), this, SLOT (handle_save()));

    // Quit button. (Part of "menu").
    QPushButton *quit = new QPushButton(this);
    quit->setText("Quit");
    quit->setObjectName("quit");
    quit->move(this->width() - 100, this->height()/2 + 5);
    quit->setMaximumSize(70, 50);
    quit->setMinimumSize(70, 50);
    QObject::connect(quit, SIGNAL (clicked()), this, SLOT (handle_quit()));

    // Init buttons for collumns.
    int pos_x = this->width()/2 - (n/2-1) * 50 - 19;
    int pos_y = this->height()/2 + n/2 * 50 + 28;
    for (int i = 0; i < button_half;)
    {
        QPushButton *ptr_1 = new QPushButton(this);
        QPushButton *ptr_2 = new QPushButton(this);
        //
        ptr_1->setText("↑");
        ptr_1->setObjectName(QString::number(i+2));
        ptr_1->move(pos_x, pos_y);
        ptr_1->setMaximumSize(40, 20);
        QObject::connect(ptr_1, SIGNAL (clicked()), this, SLOT (column_up()));
        //
        ptr_2->move(pos_x, pos_y + 18);
        ptr_2->setObjectName(QString::number(i+2));
        ptr_2->setText("↓");
        ptr_2->setMaximumSize(40, 20);
        QObject::connect(ptr_2, SIGNAL (clicked()), this, SLOT (column_down()));
        //
        i += 2;
        pos_x += 100;
    }

    // Init buttons for rows.
    pos_x = this->width()/2 + (n/2+1) * 50 - 23;
    pos_y = this->height()/2 - (n/2-1) * 50 - 18;
    for (int i = 0; i < button_half;)
    {
        QPushButton *ptr_1 = new QPushButton(this);
        QPushButton *ptr_2 = new QPushButton(this);
        //
        ptr_1->setText("←");
        ptr_1->setObjectName(QString::number(i+2));
        ptr_1->move(pos_x, pos_y);
        ptr_1->setMaximumSize(20, 40);
        ptr_1->setMinimumSize(20, 40);
        QObject::connect(ptr_1, SIGNAL (clicked()), this, SLOT (row_left()));
        //
        ptr_2->setText("→");
        ptr_2->setObjectName(QString::number(i+2));
        ptr_2->move(pos_x + 18, pos_y);
        ptr_2->setMaximumSize(20, 40);
        ptr_2->setMinimumSize(20, 40);
        QObject::connect(ptr_2, SIGNAL (clicked()), this, SLOT (row_right()));
        //
        i += 2;
        pos_y += 100;
    }
}

/**
 * @brief Widget::set_labels prepares all text fields in game
 * @param n - size of a boardfield
 */
void Widget::set_labels(int n)
{
    // Player info text.
    QLabel *player_info = new QLabel(this);
    player_info->setText("Name: .......\nColor: ......\nScore: ......");
    player_info->setFont(QFont("Courier"));
    player_info->move(this->width()/2 - n * 25 - 152, this->height()/2 - 180);

    // Labyrinth label.
    QLabel *labyrinth_lab = new QLabel(this);
    labyrinth_lab->setText("The Labyrinth");
    labyrinth_lab->setFont(QFont("Arial", 24, QFont::Bold));
    labyrinth_lab->move(this->width()/2 - 110, 15);
}

void Widget::change_player_info()
{

}

/**
 * @brief Widget::handle_quit ends whole program
 */
void Widget::handle_quit()
{
    QApplication::quit();
}

/**
 * @brief Widget::handle_save save button signal handler
 */
void Widget::handle_save()
{
    // Not implemented
    std::cerr << "click save" << std::endl;
}

/**
 * @brief Widget::handle_mute mute button signal handler
 */
void Widget::handle_mute()
{
    //Not implemented.
    std::cerr << "click mute" << std::endl;
}

/**
 * @brief Widget::handle_menu main menu button signal handler
 */
void Widget::handle_menu()
{
    //Not implemented.
    std::cerr << "click menu" << std::endl;
}

/**
 * @brief Widget::handle_rotate rotate button signal handler
 */
void Widget::handle_rotate()
{
    //Not implemented.
    std::cerr << "click rotate" << std::endl;
}

/**
 * @brief Widget::handle_undo undo button signal handler
 */
void Widget::handle_undo()
{
    //Not implemented.
    std::cerr << "click undo" << std::endl;
}

/**
 * @brief Widget::handle_next_turn next turn button signal handler
 */
void Widget::handle_next_turn()
{
    //Not implemented.
    std::cerr << "click nextt" << std::endl;
}

/**
 * @brief Widget::column_up up buttons signal handler
 */
void Widget::column_up()
{
    QObject * sender = QObject::sender();
    int pos = (sender->objectName()).toInt();
    // Not implemented
    std::cerr << "click up " << pos << std::endl;
}

/**
 * @brief Widget::column_down down buttons signal handler
 */
void Widget::column_down()
{
    QObject * sender = QObject::sender();
    int pos = (sender->objectName()).toInt();
    // Not implemented
    std::cerr << "click down " << pos << std::endl;
}

/**
 * @brief Widget::row_left left buttons signal handler
 */
void Widget::row_left()
{
    QObject * sender = QObject::sender();
    int pos = (sender->objectName()).toInt();
    // Not implemented
    std::cerr << "click left " << pos << std::endl;
}

/**
 * @brief Widget::row_right right buttons signal handler
 */
void Widget::row_right()
{
    // Not Implemented
    QObject * sender = QObject::sender();
    int pos = (sender->objectName()).toInt();
    std::cerr << "click right " << pos << std::endl;
}
