#ifndef PROJECTILE_H
#define PROJECTILE_H

/*=================================================================================*/

#include <cmath>
#include "Game.h"

/*=================================================================================*/

class Projectile
{
public:
    Projectile();
    void update();
    bool outsideWindow();
    void draw();
    SDL_Rect& getRect();

private:
    SDL_Texture* texture;
    SDL_Rect rect;
    int move_x, move_y;
    int angle;
};

/*=================================================================================*/

#endif // PROJECTILE_H
