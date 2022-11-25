#include "game.hpp"
#include "map.hpp"
#include "entities/monster_factory.hpp"
#include "inputManager/game_window.hpp"
#include "inputManager/menu_window.hpp"
#include "draw/draw_ui.hpp"
#include "algorithms/fov.hpp"
#include "draw/tile_manager.hpp"


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

    this->tileManager = new TileManager();

    codepageSmall = tileManager->LoadTexture("assets/10x10cp437.png");
    codepageBig = tileManager->LoadTexture("assets/20x20cp437.png");

    map = new Map(100,100);

    inputManager = new GameWindow();
    windows.push_back(inputManager);

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
    pemit->foreRgb = colors::yellow;
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
    redFire->glow = new Glow(redFire, colors::fire, 30);
    map->entityList.push_back(redFire);
    

    Entity * greenFire = new Entity();
    greenFire->ch = "o";
    greenFire->name = "The Green Ring";
    greenFire->object = new Object();
    greenFire->origRgb = colors::green;
    greenFire->foreRgb = colors::green;
    greenFire->posX = 31;
    greenFire->posY = 35;
    greenFire->glow = new Glow(greenFire, colors::green, 20);
    map->entityList.push_back(greenFire);

    Entity * blueFire = new Entity();
    blueFire->ch = "/";
    blueFire->name = "Aqua Wand of Menehor";
    blueFire->object = new Object();
    blueFire->origRgb = colors::blue;
    blueFire->foreRgb = colors::blue;
    blueFire->posX = 32;
    blueFire->posY = 30;
    blueFire->glow = new Glow(blueFire, colors::blue, 20);
    map->entityList.push_back(blueFire);

    Entity* rat = makeMonster(RAT, 15, 10);
    map->entityList.push_back(rat);


    player = new Entity();
    player->ch = "☺";
    player->origRgb = colors::white;
    player->foreRgb = colors::white;
    player->posX = 10;
    player->posY = 10;
    player->ai = new PlayerAi();
    player->player = new Player(player);
    player->glow = new Glow(player, colors::white, 3);
    map->entityList.push_back(player);

    Animation* arrow = new Animation();
    arrow->foreRgb = colors::red;
    arrow->backRgb = colors::blue;
    arrow->setFrames({"R","O",".","*","☺","☺"});
    arrow->posX = 5;
    arrow->speed = 1000;
    arrow->posY = 5;
    animationList.push_back(arrow);
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

void Game::update(){
    map->update();
    tileManager->update();
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
    
    for (InputManager* window : windows){
        window->render();
    }

    // draw debug info
    std::string ui = "Roguelight v0.1";
    renderText(ui, 0,0, colors::white, false);
    uint32_t tickd = SDL_GetTicks()-lastTick;
    int fps = 1000/tickd;
    std::string fpsString = std::to_string(fps);
    renderText("FPS "+fpsString, 88, 0, colors::green, false);
    lastTick = SDL_GetTicks();
    
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}