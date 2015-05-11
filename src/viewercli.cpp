/**
 * @project LABYRINTH2015
 * ICP project
 * @class ViewerCli
 * @author xsusov01
 * @email  xsusov01@stud.fit.vutbr.cz
 * @author xbandz00
 * @email  xbandz00@stud.fit.vutbr.cz
 * @file viewercli.cpp
 * @date 2015/05/10
 * @brief class for handling Viewer part of MVC decomposition in CLI mode
*/
#include <iostream>
#include "viewercli.h"
#include "strings.h"

ViewerCli::ViewerCli()
{
}

void ViewerCli::welcome()
{
    std::cout << labyrinth::welcome;
}

void ViewerCli::drawHeader(const std::string header)
{
    std::cout << header << std::endl;
}

void ViewerCli::drawBoard(const std::string boardStr)
{
    std::cout << boardStr << std::endl;
}

void ViewerCli::drawField(const std::string fieldStr)
{
    std::cout << fieldStr << std::endl;
}

void ViewerCli::drawWarnning(const std::string warrning)
{
    std::cout << warrning << std::endl;
}

void ViewerCli::drawResults(std::vector<Player *> &players)
{
     print_results(players);
}
