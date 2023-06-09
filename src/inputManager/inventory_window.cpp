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

    drawWindowAndTitle("Inventory",69,20,25,game->player->inventory.size(),colors::grey, colors::black);
    std::vector<Entity*>::iterator item;
    item = inventory.begin();
    int line = 20;
    char ascii = 97;
    while (item != inventory.end()){
        std::string letter(1,ascii);
        game->tileManager->drawSmallAsciiUI(69,line, letter,(*item)->foreRgb);
        game->tileManager->drawSmallAsciiUI(70,line, "[", colors::grey);
        game->tileManager->drawSmallAsciiUI(71,line,(*item)->ch,(*item)->foreRgb);
        game->tileManager->drawSmallAsciiUI(72,line, "]", colors::grey);
        renderText((*item)->name,73, line, colors::grey, false);
        line++;
        item++;
        ascii++;
    }
}
