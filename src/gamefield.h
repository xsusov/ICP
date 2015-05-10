#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsScene>

enum types {T, L, I};

class GameField : public QGraphicsItem
{
public:
    GameField();
};

#endif // GAMEFIELD_H
