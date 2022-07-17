#ifndef game_hpp
#define game_hpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "entities/entity.hpp"
#include "event_manager.hpp"

class Game {
public:
    Game();
    ~Game();

    Entity* player;
    int turns = 0; // turns used by the player
    std::vector< Entity* > entityList; // list of entities
    
    static SDL_Renderer *renderer;

    class Map* map;

    static SDL_Event currentEvent;

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running(){return isRunning;}

    int cnt=0;
private:
    bool isRunning;
    SDL_Window *window;
};

extern Game* game;

#endif /* game_hpp */