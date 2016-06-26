#include "Game.h"
#include "BaseState.h"

/*=================================================================================*/

namespace Game
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    SDL_Point mouse_position;
    SDL_Point window_size;
    bool running;
    float delta_time;

    namespace
    {
        int frame_rate_limit;
        StateMap states;
        std::string current_state_name;
        std::shared_ptr<BaseState> current_state;
        std::map<std::string, SDL_Texture*> textures;
        std::map<std::string, SDL_Surface*> surfaces;
        std::map<std::string, Mix_Chunk*> sounds;
        std::default_random_engine engine;
    }

    namespace Colour
    {
        SDL_Colour red = {255, 0, 0, 0};
        SDL_Colour green = {0, 255, 0, 0};
        SDL_Colour blue = {0, 0, 255, 0};
        SDL_Colour white = {255, 255, 255, 0};
    }

    /*=================================================================================*/

    void initialize(const std::string& title, const int width, const int height, const int fps_limit, const StateMap& state_map, const std::string& start_state_name)
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
        {
            throw Error::SDL;
        }

        if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
        {
            throw Error::IMG;
        }

        if (TTF_Init() == -1)
        {
            throw Error::TTF;
        }

        if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
        {
            throw Error::Mix;
        }

        window_size.x = width;
        window_size.y = height;

        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_size.x, window_size.y, SDL_WINDOW_SHOWN);
        if (window == nullptr)
        {
            throw Error::SDL;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr)
        {
            throw Error::SDL;
        }

        running = true;
        frame_rate_limit = fps_limit;

        states = state_map;
        current_state_name = start_state_name;
        current_state = states[current_state_name];

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        engine.seed(seed);
    }

    /*=================================================================================*/

    void changeState(const std::string& state_name)
    {
        current_state->shutDown();
        current_state_name = state_name;
        current_state = states[current_state_name];
        current_state->initialize();
    }

    /*=================================================================================*/

    void run()
    {
        int last_time = 0;
        int current_time = 0;
        int frame_time = 0;

        current_state->initialize();
        while (running)
        {
            // limit the frame rate by calculating the time between frames
            // and delaying if the time is less than what it should be
            last_time = current_time;
            current_time = SDL_GetTicks();
            frame_time = current_time - last_time;

            if ((1000.0 / frame_rate_limit) > frame_time)
            {
                SDL_Delay(((1000.0 / frame_rate_limit) - frame_time) * 2);
            }

            delta_time = frame_time / 1000.0;

            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    running = false;
                }
                else if (event.type == SDL_MOUSEMOTION)
                {
                    SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
                }
                else if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (event.button.button == SDL_BUTTON_RIGHT)
                    {
                        if (SDL_GetWindowGrab(window))
                        {
                            SDL_SetWindowGrab(window, SDL_FALSE);
                        }
                        else
                        {
                            SDL_SetWindowGrab(window, SDL_TRUE);
                        }
                    }
                }
                current_state->handleEvents();
            }

            current_state->update();

            SDL_RenderClear(renderer);
            current_state->draw();
            SDL_RenderPresent(renderer);
        }
        current_state->shutDown();
    }

    /*=================================================================================*/

    void shutDown()
    {
        for (auto& texture : textures)
        {
            std::cout << "Unloading texture: " << texture.first << "...";
            SDL_DestroyTexture(texture.second);
            std::cout << " Done." << std::endl;
        }

        for (auto& surface : surfaces)
        {
            std::cout << "Unloading surface: " << surface.first << "...";
            SDL_FreeSurface(surface.second);
            std::cout << " Done." << std::endl;
        }

        for (auto& sound : sounds)
        {
            std::cout << "Unloading sound: " << sound.first << "...";
            Mix_FreeChunk(sound.second);
            std::cout << " Done." << std::endl;
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    /*=================================================================================*/

    SDL_Texture* getTexture(const std::string& file_name)
    {
        if (textures.find(file_name) == textures.end())
        {
            std::cout << "Loading texture: " << file_name << "...";

            textures[file_name] = IMG_LoadTexture(renderer, file_name.c_str());
            if (textures[file_name] == nullptr)
            {
                throw Error::IMG;
            }

            std::cout << " Done." << std::endl;
        }
        return textures[file_name];
    }

    /*=================================================================================*/

    SDL_Surface* getSurface(const std::string& file_name)
    {
        if (surfaces.find(file_name) == surfaces.end())
        {
            std::cout << "Loading surface: " << file_name << "...";

            surfaces[file_name] = IMG_Load(file_name.c_str());
            if (surfaces[file_name] == nullptr)
            {
                throw Error::IMG;
            }

            std::cout << " Done." << std::endl;
        }
        return surfaces[file_name];
    }

    /*=================================================================================*/

    Mix_Chunk* getSound(const std::string& file_name)
    {
        if (sounds.find(file_name) == sounds.end())
        {
            std::cout << "Loading sound: " << file_name << "...";

            sounds[file_name] = Mix_LoadWAV(file_name.c_str());
            if (sounds[file_name] == nullptr)
            {
                throw Error::Mix;
            }

            std::cout << " Done." << std::endl;
        }
        return sounds[file_name];
    }

    /*=================================================================================*/

    int randomInteger(const int from, const int to)
    {
        std::uniform_int_distribution<int> dist(from, to);
        return dist(engine);
    }

    /*=================================================================================*/

    std::string intToString(const int value)
    {
        std::stringstream stream;
        stream << value;
        return stream.str();
    }
}
