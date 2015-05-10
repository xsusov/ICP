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