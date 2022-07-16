#ifndef game_hpp
#define game_hpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "map.hpp"
#include "entities/entity.hpp"

class Game {
public:
    Game();
    ~Game();

    Entity* player;
    std::vector< Entity* > entityList; // list of entities
    
    static SDL_Renderer *renderer;

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

#endif /* game_hpp */