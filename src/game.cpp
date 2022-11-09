#include "game.hpp"
#include "map.hpp"
#include "entities/monster_factory.hpp"
#include "inputManager/game_window.hpp"
#include "inputManager/menu_window.hpp"
#include "draw/text.hpp"

#include <iostream>

SDL_Renderer* Game::renderer = nullptr;

Game::Game(){}

Game::~Game(){}

SDL_Event Game::currentEvent;

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags = 0;
    if (fullscreen){
        //flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "Subsystems Initialized" << std::endl;
        
        SDL_Window *window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (fullscreen){
            //flags = SDL_WINDOW_FULLSCREEN;
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
        
        if (window){
            std::cout << "Window Created" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_RenderSetLogicalSize(renderer, 960, 540);
        SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
        if (renderer){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            std::cout << "Renderer Created" << std::endl;
        }

        isRunning = true;
    } else {
        std::cout << "SDL_INIT error" << std::endl;
        isRunning = false;
    }

    map = new Map(70,50);

    
    inputManager = new GameWindow();

    Entity * redFire;
    redFire = new Entity();
    redFire->ch = "*";
    redFire->origRgb = colors::fire;
    redFire->foreRgb = colors::fire;
    redFire->posX = 30;
    redFire->posY = 30;
    ParticleEmitter* pemit;
    pemit = new ParticleEmitter(redFire);
    pemit->chs = {".", ",","*","`"};
    pemit->foreRgb = colors::fireAverage;
    pemit->x = 30;
    pemit->y = 30;
    pemit->maxParticles = 10;
    pemit->spawnRate = 500;
    pemit->angle = -M_PI/2;
    pemit->speed = 0.05;
    pemit->speedSpread = 0.03;
    pemit->angleSpread = M_PI/6;
    pemit->duration = 1000;
    redFire->particleEmitter = pemit;
    redFire->glow = new Glow(redFire, colors::fire, 50);
    map->entityList.push_back(redFire);
    

    Entity * greenFire = new Entity();
    greenFire->ch = "o";
    greenFire->origRgb = colors::green;
    greenFire->foreRgb = colors::green;
    greenFire->posX = 21;
    greenFire->posY = 15;
    greenFire->glow = new Glow(greenFire, colors::green, 1);
    map->entityList.push_back(greenFire);

    Entity * blueFire = new Entity();
    blueFire->ch = "o";
    blueFire->origRgb = colors::blue;
    blueFire->foreRgb = colors::blue;
    blueFire->posX = 17;
    blueFire->posY = 20;
    blueFire->glow = new Glow(blueFire, colors::blue, 1);
    map->entityList.push_back(blueFire);

    Entity* rat = monsterFactory::makeMonster(RAT, 15, 10);
    map->entityList.push_back(rat);


    player = new Entity();
    player->ch = "☺";
    player->origRgb = colors::white;
    player->foreRgb = colors::white;
    player->posX = 10;
    player->posY = 10;
    player->ai = new PlayerAi();
    //player->glow = new Glow(player, colors::white, 1);
    map->entityList.push_back(player);

    Animation* arrow = new Animation();
    arrow->foreRgb = colors::red;
    arrow->backRgb = colors::blue;
    arrow->setFrames({"E","D",".","*","☺"});
    arrow->posX = 5;
    arrow->speed = 1000;
    arrow->posY = 5;
    animationList.push_back(arrow);
}

void Game::handleEvents(){
    /** to do turns system: when player takes action change game->turns to turns used,
     * then increment those turns into each monsters' AIs so they can do things
     * with the turns they had + the ones they have now**/

    while(SDL_PollEvent(&currentEvent)){
        inputManager->handleInput(currentEvent);
    }
}

void Game::update(){
    map->update();
    for (Entity* ent : map->entityList){
        ent->illumination = {0, 0, 0};
    }
    // first update all glowing entities
    for (Entity* ent : map->entityList){
        if (ent->glow != nullptr){
            ent->glow->update(ent);
        }   
    }
    // only then update light-receivers
    for (Entity* ent : map->entityList){
        ent->update();
       
        if (ent->foreRgb.colorDances){
            if (rand()%10 == 0){
                ent->foreRgb = colorManager::randomize(ent->origRgb);
            }
        }
        if (ent->glow){
            if (ent->glow->glowColor.colorDances){
                if (rand()%10 == 0) {
                    ent->glow->glowColor = colorManager::randomize(ent->glow->glowOrigColor);
                }
            }
        }
        
    }
}

void Game::render(){
    SDL_RenderClear(renderer);
    
    map->drawMap();
    // draw entities
    for (Entity* ent : map->entityList){
        if (ent->particleEmitter){
            ent->particleEmitter->update();
        }
        ent->render();
    }
    std::vector<Animation*>::iterator it;

    it = animationList.begin();
    while (it != animationList.end()){
        Animation* anim = *it;
        anim->render();
        
        if (anim->done == true){
            it = animationList.erase(it);
        } else {
            it++;
        }
    }
    // draw UI
    std::string ui = "Roguelight v0.1";
    renderText(ui, 0,0, colors::white, false);

    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}