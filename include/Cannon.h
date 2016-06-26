#ifndef CANNON_H
#define CANNON_H

/*=================================================================================*/

#include <cmath>
#include "Game.h"

/*=================================================================================*/

class Cannon
{
public:
    void initialize();
    void update();
    bool canShoot();
    void draw();

private:
    SDL_Texture* texture;
    SDL_Rect rect;
    int angle;
    float timer;
};

/*=================================================================================*/

#endif // CANNON_H
