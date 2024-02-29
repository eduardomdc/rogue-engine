#include "pickup_inventory_window.hpp"
#include "../game.hpp"
#include "../map.hpp"
#include "../draw/draw_ui.hpp"
#include <iostream>
#include <sstream>
#include "item_window.hpp"
#include "../animations/animation.hpp"

PickupInventoryWindow::PickupInventoryWindow(Entity* holder){
    std::cout<< "PickupInventory Window created" << std::endl;
    this->holder = holder;
}

void PickupInventoryWindow::handleInput(SDL_Event currentEvent){
    switch (currentEvent.type){
    case SDL_QUIT:
        game->isRunning = false;
        break;
    case SDL_KEYDOWN:
        switch (currentEvent.key.keysym.sym){
        case SDLK_ESCAPE:
            close();
            delete this;
            break;
        default:
            if (currentEvent.key.keysym.sym >= 97
                && currentEvent.key.keysym.sym <= 122){
                std::vector<Entity*> inventory = holder->inventory;
                int selected = currentEvent.key.keysym.sym-97;
                if (inventory.size()>selected){
                    Entity* item=inventory[selected]; 
                    game->player->inventory.push_back(item);
                    receiveAnimation(game->player, item);
                    holder->removeItem(item);
                    game->turns = 1;
                }
            } 
            break;
        }
        break;
    default:
        break;
    }
    game->turn();
}

void PickupInventoryWindow::render(){
    std::vector<Entity*> inventory = holder->inventory;
    int positionx = (game->map->mapRenderWidth/3)*2-2;
    int positiony = 2;
    int width = 2*game->map->mapRenderWidth/3;
    std::ostringstream title; 
    title<<"Items in "<<holder->name;
    drawWindowAndTitle(title.str(),positionx,positiony,width,inventory.size(),colors::grey, colors::black);
    std::vector<Entity*>::iterator item;
    item = inventory.begin();
    char ascii = 97;
    int line = positiony;
    while (item != inventory.end()){
        std::string letter(1,ascii);
        game->tileManager->drawSmallAsciiUI(positionx,line, letter,(*item)->foreRgb);
        game->tileManager->drawSmallAsciiUI(positionx+1,line, "[", colors::grey);
        game->tileManager->drawSmallAsciiUI(positionx+2,line,(*item)->ch,(*item)->foreRgb);
        game->tileManager->drawSmallAsciiUI(positionx+3,line, "]", colors::grey);
        renderText((*item)->name,positionx+4, line, colors::grey, false);
        line++;
        item++;
        ascii++;
    }
}
