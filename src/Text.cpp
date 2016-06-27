#include "Text.h"

/*=================================================================================*/

void Text::render(const std::string& font_name, const std::string& text, const SDL_Colour& colour, const int size, const int x, const int y, const bool centered, const int width)
{
    this->colour = colour;
    this->size = size;
    this->width = width;

    font = Game::getFont(font_name, size);
    setString(text);

    rect.x = x;
    rect.y = y;
    if (centered)
    {
        rect.x -= rect.w / 2;
        rect.y -= rect.h / 2;
    }
}

/*=================================================================================*/

void Text::setString(const std::string& text)
{
    SDL_Surface* text_surface;
    if (width != 0)
    {
        text_surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), colour, width);
    }
    else
    {
        text_surface = TTF_RenderText_Blended(font, text.c_str(), colour);
    }

    // we have to destroy the old texture before making a new one
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }
    texture = SDL_CreateTextureFromSurface(Game::renderer, text_surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
    SDL_FreeSurface(text_surface);
}

/*=================================================================================*/

SDL_Rect& Text::getRect()
{
    return rect;
}

/*=================================================================================*/

void Text::draw()
{
    SDL_RenderCopy(Game::renderer, texture, nullptr, &rect);
}

/*=================================================================================*/

Text::~Text()
{
    SDL_DestroyTexture(texture);
}
