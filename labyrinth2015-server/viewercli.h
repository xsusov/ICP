#ifndef VIEWERCLI_H
#define VIEWERCLI_H
#include "viewer.h"

class ViewerCli : public Viewer
{
public:
    ViewerCli();
    virtual void drawHeader(const std::string header);
    virtual void drawBoard(const std::string boardStr);
    virtual void drawField(const std::string fieldStr );
};

#endif // VIEWERCLI_H
