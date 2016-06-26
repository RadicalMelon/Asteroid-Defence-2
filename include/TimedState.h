#ifndef TIMEDSTATE_H
#define TIMEDSTATE_H

/*=================================================================================*/

#include <vector>
#include "BaseState.h"
#include "Game.h"
#include "Text.h"
#include "Cannon.h"
#include "Projectile.h"
#include "Asteroid.h"

/*=================================================================================*/

class TimedState : public BaseState
{
public:
    void initialize() override;
    void handleEvents() override;
    void update() override;
    void draw() override;
    void shutDown() override;

private:
    SDL_Texture* background;
    SDL_Rect background_rect;
    Mix_Chunk* gunfire;
    bool shooting;
    int lives;
    Text lives_text;
    float time;
    int time_old;
    Text time_text;
    float asteroid_time;
    Cannon cannon;
    std::vector<Projectile> projectiles;
    std::vector<Asteroid> asteroids;
    int asteroid_speed;
};

/*=================================================================================*/

#endif // TIMEDSTATE_H
