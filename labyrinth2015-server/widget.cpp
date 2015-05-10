#include "widget.h"
#include "gameover.h"
#include "ui_widget.h"
#include "constants.h"
#include "pixmap_ops.h"
#include "loaddialog.h"
#include "field_const.h"
#include "savedialogue.h"
#include "startdialogue.h"

#include <iostream>

#include <QGraphicsPixmapItem>
#include <QApplication>
#include <QPushButton>
#include <QKeyEvent>
#include <QObject>
#include <QString>
#include <QLabel>

/**
 * @brief Widget::Widget - cosntructor
 * @param parent - parent widget
 */
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

/**
 * @brief Widget::Widget - constructor
 * @param parent - parent widget
 * @param n - size of gameboard (5, 7, 9 or 11)
 * @param game - pointer to game
 */
Widget::Widget(QWidget *parent, int n, Game *game) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    this->game = game;
    this->game_size = n;
    this->board_scene = new QGraphicsScene;
    this->field_scene = new QGraphicsScene;
    // Set size.
    this->setFixedWidth(n * 50 + 230);
    this->setFixedHeight(n * 50 + 140);
    // UI settings.
    ui->setupUi(this);
    // Add scenes.
    ui->board_view->setScene(board_scene);
    ui->field_view->setScene(field_scene);
    // Set views fixed size.
    ui->board_view->setFixedWidth(n * 50 + 360);
    ui->board_view->setFixedHeight(n * 50 + 140);
    ui->field_view->setFixedWidth(n * 50 + 230);
    ui->field_view->setFixedHeight(n * 50 + 140);
    // Set background color: transparent.
    ui->board_view->setStyleSheet("background: transparent");
    ui->field_view->setStyleSheet("background: transparent");
}

/**
 * @brief Widget::~Widget - widget destructor.
 */
Widget::~Widget()
{
    delete ui;
}

/**
 * @brief Widget::set_buttons prepares all buttons used in widget
 * @param n - size of a boardfield.
 */
void Widget::set_buttons()
{
    // All magical constants here were carefully chossen by a professional (lol).
    // It is scientifically proven that these constants are good for your health.
    // Changing them may cause all kinds of cancer.

    // Buttons count.
    int n = this->game_size;
    int button_half = n - 1;

    // Rotate button.
    QPushButton *rotate = new QPushButton(this);
    rotate->setText("Rotate");
    rotate->setObjectName("rotate");
    rotate->move(80, this->height()/2 + 100);
    rotate->setMaximumSize(60, 25);
    QObject::connect(rotate, SIGNAL (clicked()), this, SLOT (handle_rotate()));

    // Undo button. Disabled by default.
    QPushButton *undo = new QPushButton(this);
    undo->setText("Undo");
    undo->setObjectName("undo");
    undo->move(80, this->height()/2 + 125);
    undo->setMaximumSize(60, 25);
    QObject::connect(undo, SIGNAL (clicked()), this, SLOT (handle_undo()));
    undo->setDisabled(true);

    // Next turn button. (Under rotate field scene and buttons).
    QPushButton *next_turn = new QPushButton(this);
    next_turn->setText("Next Turn");
    next_turn->setObjectName("next_turn");
    next_turn->move(19, this->height()/2 + 153);
    next_turn->setMaximumSize(121, 25);
    next_turn->setMinimumSize(121, 25);
    QObject::connect(next_turn, SIGNAL (clicked()), this, SLOT (handle_next_turn()));

    // Start button. (Part of "menu").
    QPushButton *start = new QPushButton(this);
    start->setText("New");
    start->setObjectName("new");
    start->move(this->width() - 197, this->height() - 25);
    start->setMaximumSize(50, 25);
    start->setMinimumSize(50, 25);
    QObject::connect(start, SIGNAL (clicked()), this, SLOT (handle_new()));

    // Start button. (Part of "menu").
    QPushButton *load = new QPushButton(this);
    load->setText("Load");
    load->setObjectName("load");
    load->move(this->width() - 148, this->height() - 25);
    load->setMaximumSize(50, 25);
    load->setMinimumSize(50, 25);
    QObject::connect(load, SIGNAL (clicked()), this, SLOT (handle_load()));

    // Save button. (Part of "menu").
    QPushButton *save = new QPushButton(this);
    save->setText("Save");
    save->setObjectName("save");
    save->move(this->width() - 99, this->height() - 25);
    save->setMaximumSize(50, 25);
    save->setMinimumSize(50, 25);
    QObject::connect(save, SIGNAL (clicked()), this, SLOT (handle_save()));

    // Quit button. (Part of "menu").
    QPushButton *quit = new QPushButton(this);
    quit->setText("Quit");
    quit->setObjectName("quit");
    quit->move(this->width() - 50, this->height() - 25);
    quit->setMaximumSize(50, 25);
    quit->setMinimumSize(50, 25);
    QObject::connect(quit, SIGNAL (clicked()), this, SLOT (handle_quit()));

    // Init buttons for collumns.
    int pos_x = 235;
    int pos_y = 50;
    int pos_y2 = pos_y + this->game_size * 50 + 20;
    for (int i = 0; i < button_half;)
    {
        QPushButton *ptr_1 = new QPushButton(this);
        QPushButton *ptr_2 = new QPushButton(this);
        //
        ptr_1->setText("^");
        ptr_1->setObjectName(QString::number(i+2));
        ptr_1->move(pos_x, pos_y2);
        ptr_1->setMaximumSize(40, 20);
        QObject::connect(ptr_1, SIGNAL (clicked()), this, SLOT (column_up()));
        //
        ptr_2->move(pos_x, pos_y);
        ptr_2->setObjectName(QString::number(i+2));
        ptr_2->setText(QString("v"));
        ptr_2->setMaximumSize(40, 20);
        QObject::connect(ptr_2, SIGNAL (clicked()), this, SLOT (column_down()));
        //
        this->buttons_ptr.push_back(ptr_1);
        this->buttons_ptr.push_back(ptr_2);
        i += 2;
        pos_x += 100;
    }

    // Init buttons for rows.
    int pos_x_2 = 160;
    pos_x = pos_x_2 + this->game_size * 50 + 20;
    pos_y = 125;
    for (int i = 0; i < button_half;)
    {
        QPushButton *ptr_1 = new QPushButton(this);
        QPushButton *ptr_2 = new QPushButton(this);
        //
        ptr_1->setText("<");
        ptr_1->setObjectName(QString::number(i+2));
        ptr_1->move(pos_x, pos_y);
        ptr_1->setMaximumSize(20, 40);
        ptr_1->setMinimumSize(20, 40);
        QObject::connect(ptr_1, SIGNAL (clicked()), this, SLOT (row_left()));
        //
        ptr_2->setText(">");
        ptr_2->setObjectName(QString::number(i+2));
        ptr_2->move(pos_x_2, pos_y);
        ptr_2->setMaximumSize(20, 40);
        ptr_2->setMinimumSize(20, 40);
        QObject::connect(ptr_2, SIGNAL (clicked()), this, SLOT (row_right()));
        //
        this->buttons_ptr.push_back(ptr_1);
        this->buttons_ptr.push_back(ptr_2);
        i += 2;
        pos_y += 100;
    }
}

/**
 * @brief Widget::set_labels prepares all text fields in game
 * @param n - size of a boardfield
 */
void Widget::set_labels()
{
    // Player name text.
    this->player_name = new QLabel(this);
    this->player_name->setText("            ");
    this->player_name->setFont(QFont("Arial", 13, QFont::Bold));
    this->player_name->move(20, this->height()/2 - 186);

    // Player info text.
    this->player_info = new QLabel(this);
    this->player_info->setFont(QFont("Courier", 12, QFont::Bold));
    this->player_info->move(20, this->height()/2 - 165);

    // Labyrinth label.
    QLabel *labyrinth_lab = new QLabel(this);
    labyrinth_lab->setText("The Labyrinth");
    labyrinth_lab->setFont(QFont("Arial", 20, QFont::Bold));
    labyrinth_lab->move(this->width()/2 - 60, 6);

    // Message label.
    this->message_label = new QLabel(this);
    this->message_label->setText("Message: ...                 ");
    this->message_label->setFont(QFont("Arial", 10, QFont::Bold));
    this->message_label->move(180, this->height() - 40);
}

/**
 * @brief Widget::set_log - opens log file
 */
void Widget::set_log()
{
    this->log.open(labyrinth::logfile,  std::fstream::out | std::fstream::trunc);
    if(!log.is_open())
    {
        this->message_label->setText("Error: log file not opened, rerun game!");
    }
}

char get_quest(std::string header)
{
    return header[header.length() - 2];
}


/**
 * @brief Widget::reset_scenes (re)sets the scenes
 * @param board - pointer to pixmap conating gameboard - can be empty, old pixmap will be used
 * @param field - pointer po pixmap conating free field -  can be empty, old pixmap will be used
 */
void Widget::reset_scenes(std::string board_str, std::string field_str)
{
    char quest = get_quest(this->game->getRoundHeader());
    if (!board_str.empty())
    {
        // Set board scene.
        const char **board_ptr = to_pixmap(this->game_size, board_str);
        QPixmap *board = new QPixmap(board_ptr);
        this->board_scene->clear();
        this->board_scene->addPixmap(*board);
        delete board;
        free_xpm(this->game_size, board_ptr);
    }

    if (!field_str.empty())
    {
        // Set field scene.
        const char **field_ptr = to_pixmap(1, field_str);
        const char **card_ptr = create_card(decide_color(quest), decide_shape(quest));
        QPixmap *field = new QPixmap(field_ptr);
        QPixmap *card = new QPixmap(card_ptr);
        this->field_scene->clear();
        this->field_scene->addPixmap(*field);
        this->field_scene->setSceneRect(this->width()/2 - 50, -130, 60, 60);
        // Add card.
        QGraphicsPixmapItem *card_item_ptr = this->field_scene->addPixmap(*card);
        card_item_ptr->setPos(0, -205);
        delete field;
        delete card;
        free_card(card_ptr);
        free_xpm(1, field_ptr);
    }
}

/**
 * @brief Widget::disable_buttons - disables shift and rotate buttons.
 */
void Widget::disable_buttons()
{
    for (QPushButton* ptr : this->buttons_ptr)
        ptr->setDisabled(true);

    (this->findChild<QPushButton*>("rotate"))->setDisabled(true);
}

/**
 * @brief Widget::enable_buttons - enables shift and rotate buttons.
 */
void Widget::enable_buttons()
{
    for (QPushButton* ptr : this->buttons_ptr)
        ptr->setEnabled(true);

    (this->findChild<QPushButton*>("rotate"))->setEnabled(true);
}

/**
 * @brief Widget::disable_button - disables button selected by objject name
 * @param obj_name - name of the button
 */
void Widget::disable_button(QString const obj_name)
{
    (this->findChild<QPushButton*>(obj_name))->setDisabled(true);
}

/**
 * @brief Widget::enable_button - enables button selected by objject name
 * @param obj_name - name of the button
 */
void Widget::enable_button(QString const obj_name)
{
    (this->findChild<QPushButton*>(obj_name))->setEnabled(true);
}

/**
 * @brief Widget::move_player - calls game's move method and resets scenes
 * @param direction - direction of the move
 */
void Widget::move_player(int direction)
{
    this->disable_buttons();
    this->game->move(direction);
    reset_scenes(remove_newlines(this->game->getBoardStr()),
                 remove_newlines(this->game->getFreeFieldString()));

    if (this->game->turnEnd())
    {   /// turn ends when player picks up item
        this->end_turn();
    }
}

/**
 * @brief Widget::keyPressEvent - player movement key bindings
 * @param key_ptr - key pressed
 */
void Widget::keyPressEvent(QKeyEvent *key_ptr)
{
    switch (key_ptr->key())
    {
        case Qt::Key_W: this->move_player(labyrinth::north); break;
        case Qt::Key_S: this->move_player(labyrinth::south); break;
        case Qt::Key_A: this->move_player(labyrinth::west); break;
        case Qt::Key_D: this->move_player(labyrinth::east); break;
    }
}


/**
 * @brief remove_newlines - removes newlines from string
 * @param source string with newlines
 * @return source string without newlines
 */
std::string remove_newlines(std::string source)
{
    std::string result = "";
    for (auto c : source)
    {
        if (c == '\n') continue;
        else result += c;
    }
    return result;
}

/**
 * @brief get_color - get color according to player figure
 * @param c - player figure (char)
 * @return string with color description
 */
std::string get_color(char c)
{
    switch (c)
    {
        case '@': return "BROWN ";
        case '&': return "WHITE ";
        case '%': return "RED   ";
        case '!': return "BLUE  ";
    }
    return "";
}

/**
 * @brief Widget::change_player_info - sets in game info about actual player
 * @param actual_player - pointer to Player object
 */
void Widget::change_player_info(Player *actual_player)
{
    // Player info text.
    std::string info = "";
    info = info + "Round: " + std::to_string(this->game->getRound()) + "\n";
    info = info + "Score: " + std::to_string(actual_player->getScore()) + "\n";
    info = info + "Color: " + get_color(actual_player->getFigure()) + "\n";

    this->player_info->clear();
    this->player_name->clear();
    this->player_info->setText(QString::fromStdString(info));
    this->player_name->setText(QString::fromStdString(actual_player->getName()));
}

/**
 * @brief Widget::print_message - prints message to game
 * @param message - message (QString)
 */
void Widget::print_message(QString const message)
{
    this->message_label->clear();
    this->message_label->setText("Message: " + message);
}

/**
 * @brief Widget::handle_quit - ends whole program when quit button pressed
 */
void Widget::handle_quit()
{
    delete this;
    QApplication::quit();
}

/**
 * @brief Widget::handle_new - ingamew new game button signal handler
 */
void Widget::handle_new()
{
    StartDialogue * new_game_dialogue = new StartDialogue(this, false);
    this->disable_button("new");
    new_game_dialogue->show();
}

/**
 * @brief Widget::handle_load - ingame load button signal handler
 */
void Widget::handle_load()
{
    LoadDialog * dialogue = new LoadDialog(this, false);
    this->disable_button("load");
    dialogue->show();
}

/**
 * @brief Widget::handle_save - save button signal handler
 */
void Widget::handle_save()
{
    SaveDialogue *save_dialogue = new SaveDialogue(this, this->game);
    this->disable_button("save");
    save_dialogue->show();
}

/**
 * @brief Widget::handle_rotate - rotate button signal handler
 */
void Widget::handle_rotate()
{
    this->game->getBoard()->rotateFreeField(1);
    this->reset_scenes(remove_newlines(this->game->getBoardStr()),
                       remove_newlines(this->game->getFreeFieldString()));
}

/**
 * @brief Widget::handle_undo - undo button signal handler
 */
void Widget::handle_undo()
{
    if(!this->game->isUndoPossible())
    {
        print_message("undo is not possible.");
    }
    else
    {
        this->log.close();
        if (this->game->undo())
        {
            delete this->game;
            this->game = Game::loadGame(labyrinth::tmplogfile);
            std::remove(labyrinth::tmplogfile.c_str());
            this->log.open(labyrinth::logfile, std::fstream::out | std::ios::app );
            if (!this->log.is_open())
            {
                this->print_message("Error: log file not opened, rerun game!");
            }
        }
        this->log.open(labyrinth::logfile,  std::fstream::out | std::ios::app );
        if (!this->log.is_open())
        {
            this->print_message("Error: log file not opened, rerun game!");
        }
    }
    this->reset_scenes(remove_newlines(this->game->getBoardStr()),
                       remove_newlines(this->game->getFreeFieldString()));
    this->change_player_info(this->game->get_actual_player());

    if(!this->game->isUndoPossible())
    {
        disable_button("undo");
    }
}

bool compare_players(Player * i, Player * j)
{
    return (i->getScore() < j->getScore());
}

std::string prepare_results(std::vector<Player*> &players)
{
    std::sort(players.begin(), players.end(), compare_players);
    std::string results = "";
    for (int i = players.size(); i > 0; i--)
    {
        results = results + players[i-1]->getName()
                          + "'s score is "
                          + std::to_string(players[i-1]->getScore())
                          + ".\n";
    }
    return results;
}

/**
 * @brief Widget::end_turn - ends turn, writes logs, resets buttons
 */
void Widget::end_turn()
{
    /// Check for ent game
    if (this->game->finish())
    {
        GameOver *game_over = new GameOver;
        this->disable_buttons();
        this->disable_button("save");
        this->disable_button("undo");
        this->disable_button("next_turn");
        game_over->set_results(QString::fromStdString(prepare_results(this->game->getPlayers())));
        game_over->show();
        return;
    }

    /// Writes logs
    this->log << this->game->getRoundStr();
    this->log.flush();
    /// Calls nect round.
    this->game->nextRound();
    this->reset_scenes(remove_newlines(this->game->getBoardStr()),
                       remove_newlines(this->game->getFreeFieldString()));
    this->change_player_info(this->game->get_actual_player());
    /// Enable buttons and reset message.
    this->enable_buttons();
    if (this->game->isUndoPossible())
        this->enable_button("undo");

    this->message_label->setText("Message: ...");
}

/**
 * @brief Widget::handle_next_turn - next turn button signal handler
 */
void Widget::handle_next_turn()
{
    this->end_turn();
}

/**
 * @brief Widget::column_up - shift up buttons signal handler
 */
void Widget::column_up()
{
    QObject * sender = QObject::sender();
    int pos = (sender->objectName()).toInt();
    if (this->game->shift(pos-1, labyrinth::north))
    {
        this->reset_scenes(remove_newlines(this->game->getBoardStr()),
                           remove_newlines(this->game->getFreeFieldString()));
        this->disable_buttons();
    }
}

/**
 * @brief Widget::column_down - shift down buttons signal handler
 */
void Widget::column_down()
{
    QObject * sender = QObject::sender();
    int pos = (sender->objectName()).toInt();
    if (this->game->shift(pos-1, labyrinth::south))
    {
        this->reset_scenes(remove_newlines(this->game->getBoardStr()),
                           remove_newlines(this->game->getFreeFieldString()));
        this->disable_buttons();
    }
}

/**
 * @brief Widget::row_left - shift left buttons signal handler
 */
void Widget::row_left()
{
    QObject * sender = QObject::sender();
    int pos = (sender->objectName()).toInt();
    if (this->game->shift(pos-1, labyrinth::west))
    {
        this->reset_scenes(remove_newlines(this->game->getBoardStr()),
                           remove_newlines(this->game->getFreeFieldString()));
        this->disable_buttons();
    }
}

/**
 * @brief Widget::row_right - shift right buttons signal handler
 */
void Widget::row_right()
{
    QObject * sender = QObject::sender();
    int pos = (sender->objectName()).toInt();
    if (this->game->shift(pos-1, labyrinth::east))
    {
        this->reset_scenes(remove_newlines(this->game->getBoardStr()),
                           remove_newlines(this->game->getFreeFieldString()));
        this->disable_buttons();
    }
}
