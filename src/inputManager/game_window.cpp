#include "game_window.hpp"
#include "../game.hpp"
#include "../map.hpp"
#include <iostream>
#include "menu_window.hpp"
#include "inventory_window.hpp"

GameWindow::GameWindow(){
    std::cout << "Game Window created" << std::endl;
}

void GameWindow::handleInput(SDL_Event currentEvent) {
    game->turns = 0; //after every event turns taken are set to 0 again

    switch (currentEvent.type){
    case SDL_QUIT:
        std::cout << "Quit game from game window Pressed" << std::endl;
        game->isRunning = false;
        //game->inputManager = new MenuWindow();
        break;
    case SDL_KEYDOWN:
        switch (currentEvent.key.keysym.sym){
        case SDLK_ESCAPE:
            std::cout << "Open menu window" << std::endl;
            game->windows.push_back(new MenuWindow());
            break;
        case SDLK_i:
            std::cout << "Open inventory window" << std::endl;
            game->windows.push_back(new InventoryWindow());
        default:
            game->player->ai->update(game->player);
            break;
        }
    default: // with menus this will be alot more complicated
        break;
    }

    if (game->turns){//if player took action
        for (Entity* ent : game->map->entityList){
            if (ent != game->player){
                if (ent->ai){
                    //increment turns
                    ent->ai->turns += game->turns;
                    ent->ai->update(ent);
                }
            }
        }
    }
}

void GameWindow::render(){
    game->map->drawMap();
    // draw entities
    for (Entity* ent : game->map->entityList){
        ent->render();
        if (ent->particleEmitter){
            if (game->player->player->canSee(ent->posX, ent->posY)){
                ent->particleEmitter->update();
            }
        }
    }
    std::vector<Animation*>::iterator it;

    it = game->animationList.begin();
    while (it != game->animationList.end()){
        Animation* anim = *it;
        anim->render();
        
        if (anim->done == true){
            it = game->animationList.erase(it);
        } else {
            it++;
        }
    }
}