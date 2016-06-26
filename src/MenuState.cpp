#include "MenuState.h"

/*=================================================================================*/

void MenuState::initialize()
{
    std::cout << "Entering menu." << std::endl;
    click_sound = Game::getSound("resources/sounds/click.wav");

    background = Game::getTexture("resources/images/background1.png");
    SDL_QueryTexture(background, nullptr, nullptr, &background_rect.w, &background_rect.h);
    background_rect.x = 0;
    background_rect.y = 0;

    title.render("resources/fonts/gamefont.ttf", "ASTEROID DEFENCE 2", Game::Colour::white, 36, Game::window_size.x / 2, (Game::window_size.y / 2) - 300, true);

    play_timed.initialize("resources/fonts/gamefont.ttf", "PLAY TIMED", Game::Colour::white, 24, Game::window_size.x / 2, (Game::window_size.y / 2) - 50, true);
    play_scored.initialize("resources/fonts/gamefont.ttf", "PLAY SCORED", Game::Colour::white, 24, Game::window_size.x / 2, Game::window_size.y / 2, true);
    exit.initialize("resources/fonts/gamefont.ttf", "EXIT", Game::Colour::white, 24, Game::window_size.x / 2, (Game::window_size.y / 2) + 50, true);

    timed_description.render("resources/fonts/gamefont.ttf", "THE ASTEROIDS DO NOT SPEED UP, BUT THE NUMBER OF ASTEROIDS INCREASES. TRY TO LAST AS LONG AS YOU CAN.", Game::Colour::white, 16, Game::window_size.x / 2, Game::window_size.y - 150, true, 500);
    scored_description.render("resources/fonts/gamefont.ttf", "THE NUMBER OF ASTEROIDS DOESN'T INCREASE, BUT THE SPEED OF THE ASTEROIDS DO. TRY AND BEAT THE HIGH SCORE.", Game::Colour::white, 16, Game::window_size.x / 2, Game::window_size.y - 150, true, 500);
    exit_description.render("resources/fonts/gamefont.ttf", "EXIT ASTEROID DEFENCE 2.", Game::Colour::white, 16, Game::window_size.x / 2, Game::window_size.y - 150, true, 500);
}

/*=================================================================================*/

void MenuState::handleEvents()
{
    if (Game::event.type == SDL_KEYDOWN)
    {
        if (Game::event.key.keysym.sym == SDLK_ESCAPE)
        {
            Game::running = false;
        }
    }
    else if (Game::event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (Game::event.button.button == SDL_BUTTON_LEFT)
        {
            if (play_timed.isBig())
            {
                Mix_PlayChannel(-1, click_sound, 0);
                Game::changeState("TIMED");
            }
            else if (play_scored.isBig())
            {
                Mix_PlayChannel(-1, click_sound, 0);
                Game::changeState("SCORED");
            }
            else if (exit.isBig())
            {
                Game::running = false;
            }
        }
    }
}

/*=================================================================================*/

void MenuState::update()
{
    play_timed.update();
    play_scored.update();
    exit.update();
}

/*=================================================================================*/

void MenuState::draw()
{
    SDL_RenderCopy(Game::renderer, background, nullptr, &background_rect);

    // draw buttons and text
    title.draw();
    play_timed.draw();
    play_scored.draw();
    exit.draw();

    // draw description text
    if (play_timed.isBig())
    {
        timed_description.draw();
    }
    else if (play_scored.isBig())
    {
        scored_description.draw();
    }
    else if (exit.isBig())
    {
        exit_description.draw();
    }
}

/*=================================================================================*/

void MenuState::shutDown()
{
    std::cout << "Exiting menu." << std::endl;
}
