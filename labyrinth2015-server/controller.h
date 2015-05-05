#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller
{
public:
    Controller();

    virtual int getShift(const int size, int &shiftNum, int &direction) = 0;
};

#endif // CONTROLLER_H
