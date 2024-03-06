#ifndef game_hpp
#define game_hpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_stdinc.h>
#include <iostream>
#include <vector>
#include "entities/entity.hpp"
#include "animations/animation.hpp"
#include "inputManager/input_manager.hpp"
#include "draw/tile_manager.hpp"
#include "log.hpp"

class Game {
public:
    Game();
    ~Game();

    Entity* player;
    int turns = 0; // turns used by the player
    Uint64 totalTurns = 0;  // total turns passed

    std::vector < Animation* > animationList;
    
    static SDL_Renderer *renderer;

    SDL_Texture* codepageSmall;
    SDL_Texture* codepageBig;

    int screenW, screenH; //screen resolution at fullscreen

    class Map* map;

    class TileManager* tileManager;

    class InputManager* inputManager;

    std::vector<InputManager*> windows = {}; // last item is current active window, rendered from first to last

    std::vector<msg> log; // game's text log

    InputManager* activeWindow();

    static SDL_Event currentEvent;

    uint32_t lastTick;

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    void handleEvents();
    void update();
    void render();
    void turn();
    void clean();

    SDL_Point mapToScreenCoords(int posX, int posY);

    bool running(){return isRunning;}
    bool isRunning;

    int cnt=0;
private:
    SDL_Window *window;
};

extern Game* game;

#endif /* game_hpp */
