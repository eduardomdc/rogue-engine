#include "game_window.hpp"
#include "../game.hpp"
#include "../map.hpp"
#include <SDL_keycode.h>
#include <cstdio>
#include <iostream>
#include "character_sheet.hpp"
#include "equipment_window.hpp"
#include "menu_window.hpp"
#include "inventory_window.hpp"
#include "../draw/draw_ui.hpp"

GameWindow::GameWindow(){
    std::cout << "Game Window created" << std::endl;
}

void GameWindow::handleInput(SDL_Event currentEvent) {
    game->turns = 0;
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
        case SDLK_b:
            std::cout<<"equipment window"<<std::endl;
            game->windows.push_back(new EquipmentWindow());
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
    game->turn();
}

void renderLog(){
    int posy = 1;
    int maxWidth = 20; //characters in one line
    int maxHeight = 10; // amount of log lines rendered
    int startTextY = posy+1; // where text starts
    int endTextY = startTextY+maxHeight; // where text ends
    int currentLine = endTextY;
    int currentMsg = game->log.size()-1;
    while (currentLine > posy){
        if (currentMsg >= 0){
            if (currentMsg == game->log.size()-1)
            renderText(game->log[currentMsg], 2, currentLine, colors::yellow, false);
            else
            renderText(game->log[currentMsg], 2, currentLine, colors::grey, false);
        }
        currentLine--;
        currentMsg--;
    }
}

void GameWindow::render(){
    game->map->drawMap();
    // draw entities
    for (Entity* ent : game->map->entityList.bottom){
        ent->render();
        if (ent->particleEmitter){
            if (game->player->player->canSee(ent->posX, ent->posY)){
                ent->particleEmitter->update();
            }
        }
    }
    for (Entity* ent : game->map->entityList.mid){
        ent->render();
        if (ent->particleEmitter){
            if (game->player->player->canSee(ent->posX, ent->posY)){
                ent->particleEmitter->update();
            }
        }
    }
    for (Entity* ent : game->map->entityList.top){
        ent->render();
        if (ent->particleEmitter){
            if (game->player->player->canSee(ent->posX, ent->posY)){
                ent->particleEmitter->update();
            }
        }
    }
    // draw particles
    for (Entity* ent : game->map->entityList.bottom){
        if (ent->particleEmitter){
            if (game->player->player->canSee(ent->posX, ent->posY)){
                ent->particleEmitter->render();
            }
        }
    }
    for (Entity* ent : game->map->entityList.mid){
        if (ent->particleEmitter){
            if (game->player->player->canSee(ent->posX, ent->posY)){
                ent->particleEmitter->render();
            }
        }
    }
    for (Entity* ent : game->map->entityList.top){
        if (ent->particleEmitter){
            if (game->player->player->canSee(ent->posX, ent->posY)){
                ent->particleEmitter->render();
            }
        }
    }
    
    for (int i=0; i<game->map->effects.size(); i++){
        game->map->effects[i]->render();
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
    // printf("%d game->map->mapRenderWidth*2\n", game->map->mapRenderWidth*2);
    // printf("%d game->screenW/10\n", game->screenW/10);

    drawBorder(1,1,(game->map->mapRenderWidth)*2-2,game->map->mapRenderHeight*2-2,colors::dark,colors::black);

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
    drawQuantityBar("HP", game->player->fighter->getHp(), game->player->fighter->maxHp, 1, game->screenH/10-1, 2*game->map->mapRenderWidth/3, colors::red);
    renderLog();
}
