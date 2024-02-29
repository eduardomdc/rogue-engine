#include "look.hpp"
#include <SDL_events.h>
#include <string>
#include <sstream>
#include "../game.hpp"
#include "../map.hpp"
#include "../colors.hpp"
#include "../draw/draw_ui.hpp"
#include "../draw/tile_manager.hpp"

Look::Look(){
    std::cout << "Look created" << std::endl;
    cursorX = game->player->posX;
    cursorY = game->player->posY;
}

void Look::handleInput(SDL_Event currentEvent){
    switch (currentEvent.type) {
    case SDL_QUIT:
        game->isRunning = false;
        break;
    case SDL_KEYDOWN:
        switch (currentEvent.key.keysym.sym) {
            case SDLK_ESCAPE:
            case SDLK_l:
                std::cout << "Stop looking" <<std::endl;
                close();
                delete this;
                break;
            case SDLK_w:
                cursorY--;
                break;
            case SDLK_x:
                cursorY++;
                break;
            case SDLK_a:
                cursorX--;
                break;
            case SDLK_d:
                cursorX++;
                break;
            case SDLK_q:
                cursorY--;
                cursorX--;
                break;
            case SDLK_e:
                cursorY--;
                cursorX++;
                break;
            case SDLK_z:
                cursorY++;
                cursorX--;
                break;
            case SDLK_c:
                cursorY++;
                cursorX++;
                break;
            default:
                break;
        }
    default:
        break;
    }
}

void Look::render(){
    SDL_Point screen = game->mapToScreenCoords(cursorX, cursorY);
    drawTileSelect(screen.x, screen.y);
    int things = 0; //amount of things found on that tile
    // look layers in order
    for (int i=0; i<game->map->entityList.top.size(); i++){
        Entity* ent = game->map->entityList.top[i];
        if (ent->posX == cursorX && ent->posY == cursorY){
            renderTextAndBg(" ", 2*(screen.x+1), 2*screen.y+things, colors::black, colors::black, false);
            game->tileManager->drawSmallAsciiUI(2*(screen.x+1),2*screen.y+things,ent->ch,ent->foreRgb);
            renderTextAndBg(ent->name, 2*(screen.x+1)+1, 2*screen.y+things, ent->foreRgb, colors::black, false);
            things++;
        }
    } 
    for (int i=0; i<game->map->entityList.mid.size(); i++){
        Entity* ent = game->map->entityList.mid[i];
        if (ent->posX == cursorX && ent->posY == cursorY){
            renderTextAndBg(" ", 2*(screen.x+1), 2*screen.y+things, colors::black, colors::black, false);
            game->tileManager->drawSmallAsciiUI(2*(screen.x+1),2*screen.y+things,ent->ch,ent->foreRgb);
            renderTextAndBg(ent->name, 2*(screen.x+1)+1, 2*screen.y+things, ent->foreRgb, colors::black, false);
            things++;
        }
    } 
    for (int i=0; i<game->map->entityList.bottom.size(); i++){
        Entity* ent = game->map->entityList.bottom[i];
        if (ent->posX == cursorX && ent->posY == cursorY){
            renderTextAndBg(" ", 2*(screen.x+1), 2*screen.y+things, colors::black, colors::black, false);
            game->tileManager->drawSmallAsciiUI(2*(screen.x+1),2*screen.y+things,ent->ch,ent->foreRgb);
            renderTextAndBg(ent->name, 2*(screen.x+1)+1, 2*screen.y+things, ent->foreRgb, colors::black, false);
            things++;
        }
    } 
}
