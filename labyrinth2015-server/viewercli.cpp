#include "viewercli.h"
#include <iostream>

ViewerCli::ViewerCli()
{
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
