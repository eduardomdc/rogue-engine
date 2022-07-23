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

    map = new Map(20,20);

    Entity * anvil = new Entity();
    anvil->ch = "π";
    anvil->foreRgb = colors::rusty;
    anvil->origRgb = colors::rusty;
    anvil->posX = 5;
    anvil->posY = 13;
    entityList.push_back(anvil);

    Entity * fire = new Entity();
    fire->ch = "*";
    fire->origRgb = colors::fire;
    fire->foreRgb = colors::fire;
    fire->posX = 5;
    fire->posY = 12;
    entityList.push_back(fire);

    
    Entity* rat = monsterFactory::makeMonster(RAT, 12, 12);
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
    arrow->setFrames({".","*","☺"});
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
            std::cout << "quit pressed" << std::endl;
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
    for (Entity* ent : entityList){
        if (ent->foreRgb.colorDances == true){ // to do: only randomize entities that are currently being drawn
            ent->foreRgb = colorManager::randomize(ent->origRgb);
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