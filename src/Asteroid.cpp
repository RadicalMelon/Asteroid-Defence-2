#include "Asteroid.h"

/*=================================================================================*/

Asteroid::Asteroid()
{
    initialize();
}

void Asteroid::initialize()
{
    texture = Game::getTexture("resources/images/asteroid" + Game::intToString(Game::randomInteger(1, 5)) + ".png");

    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
    rect.x = Game::randomInteger(0, Game::window_size.x - rect.w);
    rect.y = Game::randomInteger(-1000, -Game::window_size.y);

    angle = 0;
    while ((rotation_speed = Game::randomInteger(-5, 5)) == 0);
}

/*=================================================================================*/

void Asteroid::update(const int speed)
{
    rect.y += speed * Game::delta_time;

    angle += rotation_speed;
    if (angle >= 360)
    {
        angle = 0;
    }
}

/*=================================================================================*/

void Asteroid::draw()
{
    SDL_RenderCopyEx(Game::renderer, texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
}

/*=================================================================================*/

SDL_Rect& Asteroid::getRect()
{
    return rect;
}
