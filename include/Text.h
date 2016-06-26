#ifndef TEXT_H
#define TEXT_H

/*=================================================================================*/

#include "Game.h"

/*=================================================================================*/

class Text
{
public:
    void render(const std::string& font_name, const std::string& text, const SDL_Colour& colour, const int size, const int x, const int y, const bool centered, const int width = 0);
    void setString(const std::string& text);
    SDL_Rect& getRect();
    void draw();
    ~Text();

private:
    SDL_Texture* texture;
    SDL_Rect rect;
    SDL_Colour colour;
    TTF_Font* font;
    int size;
    int width;
};

/*=================================================================================*/

#endif // TEXT_H
