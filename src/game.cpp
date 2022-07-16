#include "game.hpp"
#include "map.hpp"

SDL_Renderer* Game::renderer = nullptr;

Game::Game(){}

Game::~Game(){}

SDL_Event Game::currentEvent;

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags = 0;
    if (fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "Subsystems Initialized" << std::endl;
        SDL_Window *window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window){
            std::cout << "Window Created" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            std::cout << "Renderer Created" << std::endl;
        }

        isRunning = true;
    } else {
        std::cout << "SDL_INIT error" << std::endl;
        isRunning = false;
    }

    map = new Map(20,20);

    Entity * anvil = new Entity();
    anvil->ch = "π";
    anvil->foreRgb = colors::red;
    anvil->posX = 5;
    anvil->posY = 13;
    entityList.push_back(anvil);

    player = new Entity();
    player->ch = "@";
    player->foreRgb = colors::white;
    player->posX = 10;
    player->posY = 10;
    player->ai = new PlayerAi();
    entityList.push_back(player);
}

void Game::handleEvents(){
    while(SDL_PollEvent(&currentEvent)){
        switch (currentEvent.type){
        case SDL_QUIT:
            std::cout << "quit pressed" << std::endl;
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            player->ai->update(player);
            break;
        default:
            break;
        }
    }
}

void Game::update(){
    
}

void Game::render(){
    SDL_RenderClear(renderer);
    map->drawMap();
    // draw entities
    for (Entity* ent : entityList){
        ent->render();
    }
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}