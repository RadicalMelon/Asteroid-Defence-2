#ifndef GAME_H
#define GAME_H

/*=================================================================================*/

#include <string>
#include <sstream>
#include <map>
#include <memory>
#include <iostream>
#include <random>
#include <chrono>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

/*=================================================================================*/

class BaseState;

namespace Game
{
    class BaseState
    {
    public:
        virtual void initialize() = 0;
        virtual void handleEvents() = 0;
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual void shutDown() = 0;
    };

    enum class Error
    {
        SDL,
        IMG,
        TTF,
        Mix
    };

    /*=================================================================================*/

    typedef std::map<std::string, std::shared_ptr<BaseState>> StateMap;

    extern SDL_Window* window;
    extern SDL_Renderer* renderer;
    extern SDL_Event event;
    extern SDL_Point mouse_position;
    extern SDL_Point window_size;
    extern bool running;
    extern float delta_time;

    namespace
    {
        extern int frame_rate_limit;
        extern StateMap states;
        extern std::string current_state_name;
        extern std::shared_ptr<BaseState> current_state;
        extern std::map<std::string, SDL_Texture*> textures;
        extern std::map<std::string, SDL_Surface*> surfaces;
        extern std::map<std::string, Mix_Chunk*> sounds;
        extern std::map<std::string, std::map<int, TTF_Font*>> fonts;
        extern std::default_random_engine engine;
    }

    namespace Colour
    {
        extern SDL_Colour red;
        extern SDL_Colour green;
        extern SDL_Colour blue;
        extern SDL_Colour white;
    }

    /*=================================================================================*/

    void initialize(const std::string& title, const int width, const int height, const int fps_limit, const StateMap& state_map, const std::string& start_state_name);
    void changeState(const std::string& state_name);
    void run();
    void shutDown();

    SDL_Texture* getTexture(const std::string& file_name);
    SDL_Surface* getSurface(const std::string& file_name);
    Mix_Chunk* getSound(const std::string& file_name);
    TTF_Font* getFont(const std::string& file_name, const int font_size);

    int randomInteger(const int from, const int to);
    std::string intToString(const int value);
}

/*=================================================================================*/

#endif // GAME_H
