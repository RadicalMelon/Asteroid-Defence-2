#include "Projectile.h"

/*=================================================================================*/

Projectile::Projectile()
{
    texture = Game::getTexture("resources/images/plasma.png");
    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);

    rect.x = (Game::window_size.x / 2) - (rect.w / 2);
    rect.y = (Game::window_size.y - (rect.h / 2)) - 20;

    angle = ((std::atan2((rect.y + (rect.h / 2)) - Game::mouse_position.y, (rect.x + (rect.w / 2)) - Game::mouse_position.x) * 180.0000) / 3.1416) - 90;

    float x = (rect.x + (rect.w / 2)) - Game::mouse_position.x;
    float y = (rect.y + (rect.h / 2)) - Game::mouse_position.y;

    int length = std::sqrt(std::pow(x, 2) + std::pow(y, 2));

    x /= length;
    y /= length;

    move_x = x * 1500;
    move_y = y * 1500;
}

/*=================================================================================*/

void Projectile::update()
{
    rect.x -= move_x * Game::delta_time;
    rect.y -= move_y * Game::delta_time;
}

/*=================================================================================*/

bool Projectile::outsideWindow()
{
    static SDL_Rect window_rect;
    if (SDL_RectEmpty(&window_rect))
    {
        window_rect.w = Game::window_size.x;
        window_rect.h = Game::window_size.y;
        window_rect.x = 0;
        window_rect.y = 0;
    }

    return !SDL_HasIntersection(&window_rect, &rect);
}

/*=================================================================================*/

void Projectile::draw()
{
    SDL_RenderCopyEx(Game::renderer, texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
}

/*=================================================================================*/

SDL_Rect& Projectile::getRect()
{
    return rect;
}
