#ifndef MENUSTATE_H
#define MENUSTATE_H

/*=================================================================================*/

#include "BaseState.h"
#include "Game.h"
#include "Text.h"
#include "Button.h"

/*=================================================================================*/

class MenuState : public BaseState
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
    Text title;
    Button play_timed;
    Button play_scored;
    Button exit;
    Text timed_description;
    Text scored_description;
    Text exit_description;
    Mix_Chunk* click_sound;
};

/*=================================================================================*/

#endif // MENUSTATE_H
