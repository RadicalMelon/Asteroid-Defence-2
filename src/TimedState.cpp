#include "TimedState.h"

/*=================================================================================*/

void TimedState::initialize()
{
    std::cout << "Entering timed game mode." << std::endl;

    background = Game::getTexture("resources/images/background2.png");
    SDL_QueryTexture(background, nullptr, nullptr, &background_rect.w, &background_rect.h);
    background_rect.x = 0;
    background_rect.y = 0;

    cannon.initialize();
    gunfire = Game::getSound("resources/sounds/gunfire.wav");

    for (int i = 0; i < 5; i++)
    {
        asteroids.emplace_back();
    }

    time = 0.0;
    time_old = 0;
    lives = 5;

    lives_text.render("resources/fonts/gamefont.ttf", "Lives: " + Game::intToString(lives), Game::Colour::white, 30, 20, 20, false);
    time_text.render("resources/fonts/gamefont.ttf", "Time: " + Game::intToString(static_cast<int>(time)), Game::Colour::white, 30, 20, 60, false);

    asteroid_speed = 500;
}

/*=================================================================================*/

void TimedState::handleEvents()
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

void TimedState::update()
{
    // update the timer
    time += Game::delta_time;
    if (static_cast<int>(time) > time_old)
    {
        time_old++;
        time_text.setString("TIME: " + Game::intToString(static_cast<int>(time)));
    }

    // update the timer for spawning new asteroids
    asteroid_time += Game::delta_time;
    if (asteroid_time >= 20)
    {
        std::cout << "Adding asteroid..." << std::endl;
        asteroids.emplace_back();
        asteroid_time = 0;
    }

    // update the cannon and shoot
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

    // update every asteroid and everything related
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
            }
            else
            {
                ++projectile;
            }
        }
        ++asteroid;
    }

    // update lives
    if (lives <= 0)
    {
        Game::changeState("MENU");
    }
}

/*=================================================================================*/

void TimedState::draw()
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
    time_text.draw();
}

/*=================================================================================*/

void TimedState::shutDown()
{
    std::cout << "Exiting timed game mode." << std::endl;
    projectiles.clear();
    asteroids.clear();
}
