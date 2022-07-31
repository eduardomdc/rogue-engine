#include "game.hpp"
#include "map.hpp"
#include "entities/monster_factory.hpp"
#include <iostream>

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

    map = new Map(100,100);


    Entity * sword = new Entity();
    sword->ch = "/";
    sword->foreRgb = colors::yellow;
    sword->posX = 10;
    sword->posY = 17;
    sword->glow = new Glow(sword, colors::yellow, 1);
    entityList.push_back(sword);

    Entity * sword3 = new Entity();
    sword3->ch = "/";
    sword3->origRgb = colors::grey;
    sword3->foreRgb = colors::grey;
    sword3->posX = 10;
    sword3->posY = 15;
    entityList.push_back(sword3);

    Entity * redFire = new Entity();
    redFire->ch = "*";
    redFire->origRgb = colors::fire;
    redFire->foreRgb = colors::fire;
    redFire->posX = 15;
    redFire->posY = 15;
    redFire->glow = new Glow(redFire, colors::fire, 10);
    entityList.push_back(redFire);

    Entity * greenFire = new Entity();
    greenFire->ch = "o";
    greenFire->origRgb = colors::green;
    greenFire->foreRgb = colors::green;
    greenFire->posX = 21;
    greenFire->posY = 15;
    greenFire->glow = new Glow(greenFire, colors::green, 1);
    entityList.push_back(greenFire);

    Entity * blueFire = new Entity();
    blueFire->ch = "o";
    blueFire->origRgb = colors::blue;
    blueFire->foreRgb = colors::blue;
    blueFire->posX = 17;
    blueFire->posY = 20;
    blueFire->glow = new Glow(blueFire, colors::blue, 2);
    entityList.push_back(blueFire);

    
    Entity* rat = monsterFactory::makeMonster(RAT, 15, 10);
    rat->foreRgb = colors::caveBlue;
    rat->glow = new Glow(rat, colors::caveBlue, 1);
    entityList.push_back(rat);


    player = new Entity();
    player->ch = "@";
    player->origRgb = colors::white;
    player->foreRgb = colors::white;
    player->posX = 10;
    player->posY = 10;
    player->ai = new PlayerAi();
    entityList.push_back(player);

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
        this->turns = 0; //after every event turns taken are set to 0 again

        switch (currentEvent.type){
        case SDL_QUIT:
            std::cout << "Quit Pressed" << std::endl;
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            player->ai->update(player);
            break;
        default: // with menus this will be alot more complicated
            break;
        }

        if (this->turns){//if player took action
            for (Entity* ent : entityList){
                if (ent != player){
                    if (ent->ai){
                        //increment turns
                        ent->ai->turns += this->turns;
                        ent->ai->update(ent);
                    }
                }
            }
        }
    }
}

void Game::update(){
    map->update();
    for (Entity* ent : entityList){
        ent->illumination = {0, 0, 0};
    }
    // first update all glowing entities
    for (Entity* ent : entityList){
        if (ent->glow != nullptr){
            ent->glow->update(ent);
        }   
    }
    // only then update light-receivers
    for (Entity* ent : entityList){
        ent->update();
       
        if (ent->foreRgb.colorDances){
            if (rand()%5 == 0){
                ent->foreRgb = colorManager::randomize(ent->origRgb);
                if (ent->glow->glowColor.colorDances){
                    ent->glow->glowColor = colorManager::randomize(ent->origRgb);
                }
            }
        }
        
    }
}

void Game::render(){
    SDL_RenderClear(renderer);
    map->drawMap();
    // draw entities
    for (Entity* ent : entityList){
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
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}