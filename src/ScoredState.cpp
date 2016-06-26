#include "ScoredState.h"

/*=================================================================================*/

void ScoredState::initialize()
{
    std::cout << "Entering scored game mode." << std::endl;

    background = Game::getTexture("resources/images/background3.png");
    SDL_QueryTexture(background, NULL, NULL, &background_rect.w, &background_rect.h);
    background_rect.x = 0;
    background_rect.y = 0;

    cannon.initialize();

    gunfire = Game::getSound("resources/sounds/gunfire.wav");

    for (int i = 0; i < 5; i++)
    {
        asteroids.emplace_back();
    }

    lives = 5;
    lives_text.render("resources/fonts/gamefont.ttf", "LIVES: " + Game::intToString(lives), Game::Colour::white, 30, 20, 20, false);

    score = 0;
    score_text.render("resources/fonts/gamefont.ttf", "SCORE: " + Game::intToString(score), Game::Colour::white, 30, 20, 60, false);

    speed_timer = 0.0;
    asteroid_speed = 300;
}

/*=================================================================================*/

void ScoredState::handleEvents()
{
    if (Game::event.type == SDL_KEYDOWN)
    {
        if (Game::event.key.keysym.sym == SDLK_ESCAPE)
        {
            Game::changeState("MENU");
        }
    }
    else if (Game::event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (Game::event.button.button == SDL_BUTTON_LEFT)
        {
            shooting = true;
        }
    }
    else if (Game::event.type == SDL_MOUSEBUTTONUP)
    {
        if (Game::event.button.button == SDL_BUTTON_LEFT)
        {
            shooting = false;
        }
    }
}

/*=================================================================================*/

void ScoredState::update()
{
    // update and shoot cannon
    cannon.update();
    if (shooting && cannon.canShoot())
    {
        Mix_PlayChannel(-1, gunfire, 0);
        projectiles.emplace_back();
    }

    // update every projectile
    for (auto projectile = projectiles.begin(); projectile != projectiles.end();)
    {
        projectile->update();
        if (projectile->outsideWindow())
        {
            projectiles.erase(projectile);
        }
        else
        {
            ++projectile;
        }
    }

    // update every asteroid and related
    for (auto asteroid = asteroids.begin(); asteroid != asteroids.end();)
    {
        asteroid->update(asteroid_speed);
        if (asteroid->getRect().y >= Game::window_size.y)
        {
            asteroid->initialize();
            lives_text.setString("LIVES: " + Game::intToString(--lives));
        }

        for (auto projectile = projectiles.begin(); projectile != projectiles.end();)
        {
            if (SDL_HasIntersection(&asteroid->getRect(), &projectile->getRect()))
            {
                asteroid->initialize();
                projectiles.erase(projectile);
                score_text.setString("SCORE: " + Game::intToString(++score += asteroid_speed / 50));
            }
            else
            {
                ++projectile;
            }
        }
        ++asteroid;
    }

    if (lives <= 0)
    {
        Game::changeState("MENU");
    }

    speed_timer += Game::delta_time;
    if (speed_timer >= 10)
    {
        std::cout << "Speed increased..." << std::endl;
        asteroid_speed += 50;
        speed_timer = 0;
    }
}

/*=================================================================================*/

void ScoredState::draw()
{
    SDL_RenderCopy(Game::renderer, background, NULL, &background_rect);

    for (auto& projectile : projectiles)
    {
        projectile.draw();
    }

    for (auto& asteroid : asteroids)
    {
        asteroid.draw();
    }

    cannon.draw();
    lives_text.draw();
    score_text.draw();
}

/*=================================================================================*/

void ScoredState::shutDown()
{
    std::cout << "Exiting scored game mode." << std::endl;
    projectiles.clear();
    asteroids.clear();
}
