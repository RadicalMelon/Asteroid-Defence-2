#include "Button.h"

/*=================================================================================*/

void Button::initialize(const std::string& font_name, const std::string& text, const SDL_Colour& colour, const int size, const int x, const int y, const bool centered)
{
    hover_sound = Game::getSound("resources/sounds/hover.wav");
    is_big = false;
    small_text.render(font_name, text, colour, size, x, y, centered);
    big_text.render(font_name, text, colour, size * 1.25, x, y, centered);
    current_text = &small_text;
}

/*=================================================================================*/

void Button::update()
{
    if (mouseHovering() && !is_big)
    {
        Mix_PlayChannel(-1, hover_sound, 0);
        current_text = &big_text;
        is_big = true;
    }
    else if (!mouseHovering() && is_big)
    {
        current_text = &small_text;
        is_big = false;
    }
}

/*=================================================================================*/

void Button::draw()
{
    current_text->draw();
}

/*=================================================================================*/

bool Button::mouseHovering()
{
    bool hovering_x = (Game::mouse_position.x > current_text->getRect().x) && (Game::mouse_position.x < (current_text->getRect().x + current_text->getRect().w));
    bool hovering_y = (Game::mouse_position.y > current_text->getRect().y) && (Game::mouse_position.y < (current_text->getRect().y + current_text->getRect().h));
    return hovering_x && hovering_y;
}

/*=================================================================================*/

bool Button::isBig()
{
    return is_big;
}
