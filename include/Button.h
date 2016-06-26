#ifndef BUTTON_H
#define BUTTON_H

/*=================================================================================*/

#include "Game.h"
#include "Text.h"

/*=================================================================================*/

class Button
{
public:
    void initialize(const std::string& font_name, const std::string& text, const SDL_Colour& colour, const int size, const int x, const int y, const bool centered);
    void update();
    void draw();
    bool mouseHovering();
    bool isBig();

private:
    bool is_big;
    Text small_text;
    Text big_text;
    Text* current_text;
    Mix_Chunk* hover_sound;
};

/*=================================================================================*/

#endif // BUTTON_H
