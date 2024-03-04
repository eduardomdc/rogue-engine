#include "game.hpp"
#include "colors.hpp"
#include "entities/entity.hpp"
#include "map.hpp"
#include "factories/monster_factory.hpp"
#include "inputManager/game_window.hpp"
#include "inputManager/menu_window.hpp"
#include "draw/draw_ui.hpp"
#include "algorithms/fov.hpp"
#include "draw/tile_manager.hpp"
#include "particles/effect.hpp"

#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

SDL_Renderer* Game::renderer = nullptr;

Game::Game(){
    log = {};
}

Game::~Game(){}

SDL_Event Game::currentEvent;

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags = 0;
    
    if (fullscreen){
        flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "Subsystems Initialized" << std::endl;
        
        SDL_Window *window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        
        if (window){
            std::cout << "Window Created" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        //SDL_RenderSetLogicalSize(renderer, 960, 540);
        //SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
        if (renderer){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            std::cout << "Renderer Created" << std::endl;
        }

        isRunning = true;
    } else {
        std::cout << "SDL_INIT error" << std::endl;
        isRunning = false;
    }
    //get window resolution
    SDL_GetRendererOutputSize(renderer, &screenW, &screenH);
    std::cout<<screenW<<"x"<<screenH<<std::endl;
    this->tileManager = new TileManager();

    codepageSmall = tileManager->LoadTexture("assets/10x10cp437.png");
    codepageBig = tileManager->LoadTexture("assets/20x20cp437.png");

    

    map = new Map(50,50);
    
    map->genMap();
    player = new Entity();
    player->ch = "☺";
    player->name = "Player";
    player->origRgb = colors::white;
    player->foreRgb = colors::white;
    player->posX = 10;
    player->posY = 10;
    player->ai = new PlayerAi(player);
    player->player = new Player(player);
    player->fighter = new Fighter(player);
    player->fighter->maxHp = 100;
    player->fighter->str = 10;
    player->fighter->agi = 10;
    player->fighter->con = 10;
    player->fighter->setHp(100);
    map->entityList.push_back(player);
    inputManager = new GameWindow();
    windows.push_back(inputManager);

    
}

InputManager* Game::activeWindow(){
    // returns last window on the list
    try{
        return windows.back();
    }
    catch (...){
        std::cout << "Game::activeWindow() error"<<std::endl;
        return nullptr;
    }
}

void Game::handleEvents(){
    /** to do turns system: when player takes action change game->turns to turns used,
     * then increment those turns into each monsters' AIs so they can do things
     * with the turns they had + the ones they have now**/

    while(SDL_PollEvent(&currentEvent)){
        // get current active window to handle input
        activeWindow()->handleInput(currentEvent);
    }
}

void zeroingLight(std::vector<Entity*> entityList){
    for (int i=0; i<entityList.size(); i++){
        entityList[i]->illumination = {0,0,0};
    }
}

void updateGlows(std::vector<Entity*> entityList){
    for (int i=0; i<entityList.size(); i++){
        if (entityList[i]->glow != nullptr){
            entityList[i]->glow->update(entityList[i]);
            if (entityList[i]->glow->glowColor.colorDances){
                if (rand()%10 == 0) {
                    entityList[i]->glow->glowColor = colorManager::randomize(entityList[i]->glow->glowOrigColor);
                }
            }
        }
    }
}

void updateEffects(std::vector<Effect*> effects){
    for (int i=0; i<effects.size(); i++){
        effects[i]->ent->update();
        if (effects[i]->ent->glow != nullptr){
            effects[i]->ent->glow->update(effects[i]->ent);
            if (effects[i]->ent->glow->glowColor.colorDances){
                if (rand()%10 == 0) {
                    effects[i]->ent->glow->glowColor = colorManager::randomize(effects[i]->ent->glow->glowOrigColor);
                }
            }
        }
    }
}

void updateLightReceivers(std::vector<Entity*> entityList){
    for (int i=0; i<entityList.size(); i++){
        entityList[i]->update();
       
        if (entityList[i]->foreRgb.colorDances){
            if (rand()%10 == 0){
                entityList[i]->foreRgb = colorManager::randomize(entityList[i]->origRgb);
            }
        }

    }
}

SDL_Point Game::mapToScreenCoords(int posX, int posY){
    SDL_Point screen;
    screen.x = posX - map->leftSide + map->mapOffsetX;
    screen.y = posY - map->topSide + map->mapOffsetY;
    return screen;
}

void Game::update(){
    map->update();
    tileManager->update();
    zeroingLight(map->entityList.bottom);
    zeroingLight(map->entityList.mid);
    zeroingLight(map->entityList.top);
    // first update all glowing entities
    updateGlows(map->entityList.bottom);
    updateGlows(map->entityList.mid);
    updateGlows(map->entityList.top);
    updateEffects(map->effects);
    // only then update light-receivers
    updateLightReceivers(map->entityList.bottom);
    updateLightReceivers(map->entityList.mid);
    updateLightReceivers(map->entityList.top);
}

void Game::turn(){
    // game turns
    if (game->turns && game->player->player->walkQueue.size() == 0){//if player took action
        game->totalTurns++;
        auto ent = game->map->entityList.top.begin();
        while (ent != game->map->entityList.top.end()){
            if (*ent != game->player){
                if ((*ent)->ai != nullptr){
                    //increment turns
                    (*ent)->ai->update();
                }
            }
            if ((*ent)->fighter != nullptr){
                (*ent)->fighter->update();
            }
            ent++;
        }
    }
    game->turns = 0;
    // else if (game->player->player->walkQueue.size() > 0){
    //     while (game->player->player->walkQueue.size() > 0){
    //         lastMoveTick = SDL_GetTicks();
    //         while(SDL_GetTicks()-lastMoveTick < 10){
    //             game->update();
    //             game->render();
    //         }
    //         game->player->ai->update();
    //         for (Entity* ent : game->map->entityList.top){
    //             if (ent != game->player){
    //                 if (ent->ai != nullptr){
    //                     //increment turns
    //                     ent->ai->update();
    //                 }
    //             }
    //         }
    //     }
    // }
}

void Game::render(){
    SDL_RenderClear(renderer);
    
    for (InputManager* window : windows){
        window->render();
    }

    // draw debug info
    uint32_t tickd = SDL_GetTicks()-lastTick;
    int fps = 1000/(tickd+1);
    std::string fpsString = std::to_string(fps);
    renderText("FPS "+fpsString, 2*map->mapRenderWidth-20, 0, colors::yellow, false);
    std::ostringstream turnsstring;
    turnsstring << "TURN "<<totalTurns;
    renderText(turnsstring.str(), 2*map->mapRenderWidth-40, 0, colors::yellow, false);
    lastTick = SDL_GetTicks();
    
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}
