/**
 * @project LABYRINTH2015
 * ICP project
 * @author xsusov01
 * @email  xsusov01@stud.fit.vutbr.cz
 * @author xbandz00
 * @email  xbandz00@stud.fit.vutbr.cz
 * @file main.cpp
 * @date 2015/05/10
 * @brief main GUI source file
*/

#include "menu.h"
#include "widget.h"

#include <vector>
#include <string>

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
    /// feed time for randomize
    std::srand(time(NULL));
    /// open and show menu
    Menu m(0);
    m.show();

    return a.exec();
    return 0;
}
