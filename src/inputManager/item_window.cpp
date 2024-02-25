#include "item_window.hpp"
#include <SDL_events.h>
#include <string>
#include <sstream>
#include "../game.hpp"
#include "../colors.hpp"
#include "../draw/draw_ui.hpp"
#include "../draw/tile_manager.hpp"

ItemWindow::ItemWindow(Entity* item){
    std::cout << "Item window created" << std::endl;
    this->item = item;
}

void ItemWindow::handleInput(SDL_Event currentEvent){
    switch (currentEvent.type) {
    case SDL_QUIT:
        game->isRunning = false;
        break;
    case SDL_KEYDOWN:
        switch (currentEvent.key.keysym.sym) {
            case SDLK_ESCAPE:
                std::cout << "Close item window" <<std::endl;
                close();
                delete this;
                break;
            case SDLK_e:
                std::cout << "Equip item!"<<std::endl;
                if (game->player->fighter->equipItem(this->item)){
                    game->turns = 1;
                    game->turn();
                    close();
                    delete this;
                }
                break;
            case SDLK_d:
                std::cout << "Drop item!"<<std::endl;
                game->player->drop(this->item);
                close();
                delete this;
                break;
            case SDLK_u:
                if (item->item->type==itemType::USABLE){
                    item->item->use(game->player, item);
                    game->turns = 1;
                    game->turn();
                    close();
                    delete this;
                }
            default:
                break;
        }
    default:
        break;
    }
}

void renderItemInfo(Entity* item, int posX, int posY, int width, int height){
    drawWindowAndTitle(item->name, posX, posY, width, height, colors::grey, colors::black);
    SDL_Texture* codepage = game->codepageBig;
    SDL_Rect src;
    SDL_Rect dest;
    dest.x = (posX+width/2-1)*10;
    dest.y = (posY+1)*10;
    game->tileManager->drawAscii(codepage,src,dest,item->ch,item->foreRgb,20,20,16, 16);
    if (item->item->type == itemType::NONE){
        std::string type = "[Object]";
        renderText(type, posX+width/2, posY+4, colors::grey, true);
    }
    if (item->item->type == itemType::WEAPON){
        std::string type = "[Weapon]";
        renderText(type, posX+width/2, posY+4, colors::grey, true);
        std::string damage = "Damage "; 
        damage.append(std::to_string(item->item->dieAmount));
        damage.append("d");
        damage.append(std::to_string(item->item->damageDie));
        if (item->item->damageMod){
            damage.append("+");
            damage.append(std::to_string(item->item->damageMod));
        }
        renderText(damage, posX, posY+5, colors::red, false);
    }
    if (item->item->type == itemType::USABLE){
        std::string type = "[Usable]";
        renderText(type, posX+width/2, posY+4, colors::grey, true);
    }
    std::ostringstream weight;
    weight<<"W";
    weight.precision(2);
    weight<<(item->item->weight);
    weight<<"Kg";
    renderText(weight.str(), posX, posY+6, colors::grey, false);
}


void ItemWindow::render(){
    int posX = 2;
    int posY = 2;
    int width = 16;
    int height = 22;
    renderItemInfo(item, posX, posY, width, height);

    if (item->item->equipable)
        renderText("[e] to equip", posX, posY+20, colors::grey, false);
    if (item->item->type == itemType::USABLE)
        renderText("[u] to use", posX, posY+19, colors::grey, false);
    renderText("[d] to drop", posX, posY+21, colors::grey, false);
}
