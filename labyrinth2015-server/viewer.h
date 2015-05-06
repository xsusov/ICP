#ifndef VIEWER_H
#define VIEWER_H
#include <string>
#include "player.h"

class Viewer
{
public:
    Viewer();

    virtual void welcome() = 0;
    virtual void drawHeader(const std::string header) = 0;
    virtual void drawBoard(const std::string header) = 0;
    virtual void drawField(const std::string fieldStr) = 0;
    virtual void drawWarnning(const std::string warrning) = 0;
    virtual void drawResults(std::vector<Player*> &players) = 0;
};

#endif // VIEWER_H
