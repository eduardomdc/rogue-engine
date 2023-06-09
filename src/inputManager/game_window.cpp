#include "game_window.hpp"
#include "../game.hpp"
#include "../map.hpp"
#include <SDL_keycode.h>
#include <iostream>
#include "character_sheet.hpp"
#include "menu_window.hpp"
#include "inventory_window.hpp"
#include "../draw/draw_ui.hpp"

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
            break;
        case SDLK_TAB:
            std::cout<<"Open character window"<<std::endl;
            game->windows.push_back(new CharacterSheet());
            break;
        default:
            game->player->ai->update();
            break;
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        game->player->ai->update();
        break;
    case SDL_MOUSEMOTION:
        this->mouseX = currentEvent.button.x;
        this->mouseY = currentEvent.button.y;
    default:
        break;
    }

    if (game->turns && game->player->player->walkQueue.size() == 0){//if player took action
        for (Entity* ent : game->map->entityList){
            if (ent != game->player){
                if (ent->ai != nullptr){
                    //increment turns
                    ent->ai->turns += game->turns;
                    ent->ai->update();
                }
            }
        }
    }
    else if (game->player->player->walkQueue.size() > 0){
        while (game->player->player->walkQueue.size() > 0){
            lastMoveTick = SDL_GetTicks();
            while(SDL_GetTicks()-lastMoveTick < 10){
                game->update();
                game->render();
            }
            game->player->ai->update();
            for (Entity* ent : game->map->entityList){
                if (ent != game->player){
                    if (ent->ai != nullptr){
                        //increment turns
                        ent->ai->turns += game->turns;
                        ent->ai->update();
                    }
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
        } else if ( anim->onMap ){ 
            if (!game->map->inCamera((*it)->posX, (*it)->posY)
                || !game->player->player->canSee(anim->posX, anim->posY)){
                it = game->animationList.erase(it);
            }
            else {
                it++;
            }
        } 
        else {
            it++;
        }
    }

    drawBorder(1,1,94,52,colors::dark,colors::black);

    /** mouse support!!
    int screenX = this->mouseX/20;
    int screenY = this->mouseY/20;
    int x = screenX + game->map->leftSide - game->map->mapOffsetX;
    int y = screenY + game->map->topSide - game->map->mapOffsetY;
    std::list<position> path = straightPath({game->player->posX, game->player->posY}, {x, y});
    std::list<position>::iterator itui;
    itui = path.begin();
    while (itui != path.end()){
        int tileX = itui->x - game->map->leftSide + game->map->mapOffsetX;
        int tileY = itui->y - game->map->topSide + game->map->mapOffsetY;
        drawTileSelect(tileX, tileY);
        itui++;
    }
    **/

    // draw health
    drawQuantityBar("HP", game->player->fighter->getHp(), game->player->fighter->maxHp, 1, 53, 15, colors::red);
}
