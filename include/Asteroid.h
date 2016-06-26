#ifndef ASTEROID_H
#define ASTEROID_H

/*=================================================================================*/

#include "Game.h"

/*=================================================================================*/

class Asteroid
{
public:
    Asteroid();
    void initialize();
    void update(const int speed);
    void draw();
    SDL_Rect& getRect();

private:
    SDL_Texture* texture;
    SDL_Rect rect;
    int angle;
    int rotation_speed;
};

/*=================================================================================*/

#endif // ASTEROID_H
