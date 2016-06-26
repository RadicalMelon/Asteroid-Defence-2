#include "Cannon.h"

/*=================================================================================*/

void Cannon::initialize()
{
    texture = Game::getTexture("resources/images/cannon.png");
    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);

    rect.x = (Game::window_size.x / 2) - (rect.w / 2);
    rect.y = (Game::window_size.y - (rect.h / 2)) - 20;

    angle = 0;
}

/*=================================================================================*/

void Cannon::update()
{
    timer += Game::delta_time;
    angle = ((std::atan2((rect.y + (rect.h / 2)) - Game::mouse_position.y, (rect.x + (rect.w / 2)) - Game::mouse_position.x) * 180.0000) / 3.1416) - 90;
}

/*=================================================================================*/

bool Cannon::canShoot()
{
    if (timer >= 0.2)
    {
        timer = 0;
        return true;
    }
    return false;
}

/*=================================================================================*/

void Cannon::draw()
{
    SDL_RenderCopyEx(Game::renderer, texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
}
