#include "inventory_window.hpp"
#include "../game.hpp"
#include "../map.hpp"
#include "../draw/draw_ui.hpp"
#include <iostream>

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
        }
        break;
    default:
        break;
    }
}

void InventoryWindow::render(){
    std::vector<Entity> inventory = game->player->player->inventory;

    drawWindow(70,20,23,20);
    std::vector<Entity>::iterator item;
    item = inventory.begin();
    int line = 20;
    while (item != inventory.end()){
        TileManager::drawSmallAsciiUI(70,line,item->ch,item->foreRgb);
        renderText(item->name,71, line, colors::white, false);
        line++;
        item++;
    }
}