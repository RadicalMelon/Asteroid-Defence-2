#ifndef BASESTATE_H
#define BASESTATE_H

/*=================================================================================*/

class BaseState
{
public:
    virtual void initialize() = 0;
    virtual void handleEvents() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void shutDown() = 0;
};

/*=================================================================================*/

#endif // BASESTATE_H
