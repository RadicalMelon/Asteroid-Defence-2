#ifndef SCOREDSTATE_H
#define SCOREDSTATE_H

/*=================================================================================*/

#include <vector>
#include "Game.h"
#include "Cannon.h"
#include "Projectile.h"
#include "Asteroid.h"
#include "Text.h"

/*=================================================================================*/

class ScoredState : public Game::BaseState
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
    Cannon cannon;
    bool shooting;
    std::vector<Projectile> projectiles;
    Mix_Chunk* gunfire;
    std::vector<Asteroid> asteroids;
    Text lives_text;
    int lives;
    Text score_text;
    int score;
    float speed_timer;
    int asteroid_speed;
};

/*=================================================================================*/

#endif // SCOREDSTATE_H
