#include <SDL2/SDL.h>
#include "main.hpp"
#include "map.hpp"

Game* game;

int main(int argc, char *argv[]){
    // get random seed
    srand((unsigned int)time(NULL));

    const int FPS = 10;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("Rogue", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, false);

    while (game->running()){

        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime){
            SDL_Delay(frameDelay-frameTime);
        }
    }

    game->clean();

    return 0;
}