#ifndef VIEWER_H
#define VIEWER_H
#include <string>

class Viewer
{
public:
    Viewer();

    virtual void drawHeader(const std::string header) = 0;
    virtual void drawBoard(const std::string header) = 0;
    virtual void drawField(const std::string fieldStr) = 0;
    virtual void drawWarnning(const std::string warrning) = 0;
};

#endif // VIEWER_H
