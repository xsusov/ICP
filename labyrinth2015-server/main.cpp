#include "menu.h"
#include "widget.h"

#include <vector>
#include <string>
#include <iostream>

#include <QLabel>
#include <QtCore>
#include <QPixmap>
#include <QString>
#include <QPushButton>
#include <QApplication>
#include <QGraphicsScene>
#include <QCoreApplication>
#include <QGraphicsRectItem>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::srand(time(NULL));

    Menu m(0);
    m.show();

    /*
     *
     * // Do stuff.
    std::string brd = "XXXXXXXXXXXXXXXXXXXXXXXXXX@  XX   XX   XX   XX&  XX    X g    k    l      XX   XX   XX   XX   XX   XXX XXXX XXXX XXXXXXXXX XXXX XXXXXXXXXXXXXX XXXX XXX   XX   XX   XX   XX   XX   XX a       X    X   XX   XX   XX   XX   XX   XXX XXXX XXXXXXXXXXXXXX XXXX XXXXXXXXX XXXX XXXX XXX   XX   XX   XX   XX   XX c    d      XX   X  j XX   XX   XX   XX   XX   XXX XXXX XXXX XXXX XXXX XXXX XXXXXXXXX XXXX XXXX XXX   XX   XX   XX   XX   XX b    e X       h X  f XX   XX   XX   XX   XX   XXXXXXXX XXXXXXXXXXXXXX XXXX XXXX XXXX XXXX XXXX XXX   XX   XX   XX   XX   XX i                X    XX   XX   XX   XX   XX   XXXXXXXXXXXXXXXXXXXXXXXXXX";
    std::string fld = "XX XXX   XX i  X   XXXXXX";

    w->reset_scenes(n, brd, fld);
    w->set_buttons(n);
    w->set_labels(n);

    // Show game and hide menu.
    w->show();
    */
    return a.exec();
    return 0;
}
