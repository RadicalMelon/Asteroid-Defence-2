#include <iostream>
#include "MenuState.h"
#include "TimedState.h"
#include "ScoredState.h"

/*=================================================================================*/

int main(int argc, char* argv[])
{
    Game::StateMap states =
    {
        {
            "MENU", std::make_shared<MenuState>()
        },
        {
            "TIMED", std::make_shared<TimedState>()
        },
        {
            "SCORED", std::make_shared<ScoredState>()
        }
    };

    try
    {
        Game::initialize("Asteroid Defence 2", 600, 800, 60, states, "MENU");

        SDL_Surface* cursor_surface = Game::getSurface("resources/images/crosshair.png");
        SDL_Cursor* cursor = SDL_CreateColorCursor(cursor_surface, cursor_surface->w / 2, cursor_surface->h / 2);
        SDL_SetCursor(cursor);
        SDL_SetWindowGrab(Game::window, SDL_TRUE);

        Game::run();
        Game::shutDown();

        SDL_FreeCursor(cursor);
    }
    catch (Game::Error error)
    {
        switch (error)
        {
        case Game::Error::SDL:
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error", SDL_GetError(), Game::window);
            std::cout << "SDL Error: " << SDL_GetError() << std::endl;
            break;
        case Game::Error::IMG:
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "IMG Error", IMG_GetError(), Game::window);
            std::cout << "IMG Error: " << IMG_GetError() << std::endl;
            break;
        case Game::Error::TTF:
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "TTF Error", TTF_GetError(), Game::window);
            std::cout << "TTF Error: " << TTF_GetError() << std::endl;
            break;
        case Game::Error::Mix:
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Mix Error", Mix_GetError(), Game::window);
            std::cout << "Mix Error: " << Mix_GetError() << std::endl;
        default:
            break;
        }

        if (SDL_GetWindowGrab(Game::window))
        {
            SDL_SetWindowGrab(Game::window, SDL_FALSE);
        }
        Game::shutDown();

        std::cin.get();
    }

    return 0;
}
