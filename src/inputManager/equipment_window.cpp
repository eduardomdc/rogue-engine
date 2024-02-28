#include "equipment_window.hpp"
#include "../game.hpp"
#include "../map.hpp"
#include "equipped_item_window.hpp"
#include "../draw/draw_ui.hpp"


EquipmentWindow::EquipmentWindow(){
    return;
}

void EquipmentWindow::handleInput(SDL_Event currentEvent){
    std::vector<Entity*>* equipments = game->player->fighter->equipments;
    switch (currentEvent.type){
    case SDL_QUIT:
        game->isRunning = false;
        break;
    case SDL_KEYDOWN:
        switch (currentEvent.key.keysym.sym){
        case SDLK_ESCAPE:
        case SDLK_b:
            std::cout << "Close equipment window" << std::endl;
            close();
            delete this;
            break;
        // default:
        //     if (currentEvent.key.keysym.sym >= 97
        //         && currentEvent.key.keysym.sym <= 122){
        //         std::vector<Entity*>* equipments = game->player->fighter->equipments;
        //         int selected = currentEvent.key.keysym.sym-97;

        //         // if (equipments->size()>selected){
        //         //     Entity* item=inventory[selected]; 
        //         //     game->windows.push_back(new ItemWindow(item));
        //         // }
        //     } 
        //     break;
        case SDLK_w:
            if ((*equipments)[equipSlots::HEAD] != nullptr){
                std::cout << "Head equipment selected" << std::endl;
                Entity* item = (*equipments)[equipSlots::HEAD];
                game->windows.push_back(new EquippedItemWindow(item));
            }
            break;
        case SDLK_r:
            if ((*equipments)[equipSlots::NECK] != nullptr){
                Entity* item = (*equipments)[equipSlots::NECK];
                game->windows.push_back(new EquippedItemWindow(item));
            }
            break;
        case SDLK_s:
            if ((*equipments)[equipSlots::BODY] != nullptr){
                Entity* item = (*equipments)[equipSlots::BODY];
                game->windows.push_back(new EquippedItemWindow(item));
            }
            break;
        case SDLK_x:
            if ((*equipments)[equipSlots::LEG] != nullptr){
                Entity* item = (*equipments)[equipSlots::LEG];
                game->windows.push_back(new EquippedItemWindow(item));
            }
            break;
        case SDLK_a:
            if ((*equipments)[equipSlots::HAND1] != nullptr){
                std::cout << "Hand1 equipment selected" << std::endl;
                Entity* item = (*equipments)[equipSlots::HAND1];
                game->windows.push_back(new EquippedItemWindow(item));
            }
            break;
        case SDLK_d:
            if ((*equipments)[equipSlots::HAND2] != nullptr){
                std::cout << "Hand1 equipment selected" << std::endl;
                Entity* item = (*equipments)[equipSlots::HAND2];
                game->windows.push_back(new EquippedItemWindow(item));
            }
            break;
        case SDLK_z:
            if ((*equipments)[equipSlots::FEET] != nullptr){
                Entity* item = (*equipments)[equipSlots::FEET];
                game->windows.push_back(new EquippedItemWindow(item));
            }
            break;
        case SDLK_q:
            if ((*equipments)[equipSlots::RING1] != nullptr){
                Entity* item = (*equipments)[equipSlots::RING1];
                game->windows.push_back(new EquippedItemWindow(item));
            }
            break;
        case SDLK_e:
            if ((*equipments)[equipSlots::RING2] != nullptr){
                Entity* item = (*equipments)[equipSlots::RING2];
                game->windows.push_back(new EquippedItemWindow(item));
            }
            break;
        }
        break;
    default:
        break;
    }
}

void renderSlot(equipSlots::equipSlots slot, int px, int py){
    std::vector<Entity*>* equipments = game->player->fighter->equipments;
    game->tileManager->drawSmallAsciiUI(px-1,py, "[", colors::grey);
    if ((*equipments)[slot] != nullptr)
        game->tileManager->drawSmallAsciiUI(px,py, (*equipments)[slot]->ch, (*equipments)[slot]->foreRgb);
    game->tileManager->drawSmallAsciiUI(px+1,py, "]", colors::grey);
}

void EquipmentWindow::render(){
    std::vector<Entity*>* equipments = game->player->fighter->equipments;
    int px = (game->map->mapRenderWidth/3)*2-2;
    int py = 2;
    int width = 25;
    int height = 25;
    drawWindowAndTitle("Equipment",px,py,width,height,colors::grey, colors::black);
    game->tileManager->drawSmallAsciiUI(px+width/2-2,py+2, "w", colors::white);
    renderSlot(equipSlots::HEAD, px+width/2, py+2);
    game->tileManager->drawSmallAsciiUI(px+width/2-2,py+4, "r", colors::white);
    renderSlot(equipSlots::NECK, px+width/2, py+4);
    game->tileManager->drawSmallAsciiUI(px+width/2-2,py+7, "s", colors::white);
    renderSlot(equipSlots::BODY, px+width/2, py+7);
    game->tileManager->drawSmallAsciiUI(px+width/3-2,py+8, "a", colors::white);
    renderSlot(equipSlots::HAND1, px+width/3, py+8);
    game->tileManager->drawSmallAsciiUI(px+2*width/3-2,py+8, "d", colors::white);
    renderSlot(equipSlots::HAND2, px+2*width/3, py+8);
    game->tileManager->drawSmallAsciiUI(px+width/3-2,py+5, "q", colors::white);
    renderSlot(equipSlots::RING1, px+width/3, py+5);
    game->tileManager->drawSmallAsciiUI(px+2*width/3-2,py+5, "e", colors::white);
    renderSlot(equipSlots::RING2, px+2*width/3, py+5);
    game->tileManager->drawSmallAsciiUI(px+width/2-2,py+10, "x", colors::white);
    renderSlot(equipSlots::LEG, px+width/2, py+10);
    game->tileManager->drawSmallAsciiUI(px+width/2-2,py+12, "z", colors::white);
    renderSlot(equipSlots::FEET, px+width/2, py+12);
}
