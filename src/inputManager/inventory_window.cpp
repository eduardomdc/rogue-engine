#include "inventory_window.hpp"
#include "../game.hpp"
#include "../map.hpp"
#include "../draw/draw_ui.hpp"
#include <iostream>
#include "item_window.hpp"

InventoryWindow::InventoryWindow(){
    std::cout<< "Inventory Window created" << std::endl;
}

void InventoryWindow::handleInput(SDL_Event currentEvent){
    switch (currentEvent.type){
    case SDL_QUIT:
        game->isRunning = false;
        break;
    case SDL_KEYDOWN:
        switch (currentEvent.key.keysym.sym){
        case SDLK_ESCAPE:
            std::cout << "Close inventory window" << std::endl;
            close();
            delete this;
            break;
        default:
            if (currentEvent.key.keysym.sym >= 97
                && currentEvent.key.keysym.sym <= 122){
                std::vector<Entity*> inventory = game->player->inventory;
                int selected = currentEvent.key.keysym.sym-97;
                if (inventory.size()>selected){
                    Entity* item=inventory[selected]; 
                    game->windows.push_back(new ItemWindow(item));
                }
            } 
            break;
        }
        break;
    default:
        break;
    }
}

void InventoryWindow::render(){
    std::vector<Entity*> inventory = game->player->inventory;
    int positionx = 69;
    int positiony = 20;
    drawWindowAndTitle("Inventory",positionx,positiony,25,game->player->inventory.size(),colors::grey, colors::black);
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
