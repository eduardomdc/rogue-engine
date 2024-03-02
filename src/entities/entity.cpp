#include "entity.hpp"
#include "tile.hpp"
#include <iostream>
#include <algorithm>
#include <list>
#include "../draw/tile_manager.hpp"
#include "../game.hpp"
#include "../map.hpp"
#include "../algorithms/fov.hpp"
#include "../animations/animation.hpp"
#include "../inputManager/pickup_inventory_window.hpp"

Entity::Entity(){
    this->foreRgb = colors::white;
    this->backRgb = colors::black;
    this->visible = true;
    this->stepOn = nullptr;
    this->inventory = {};
};

Entity::~Entity(){
    if (item != nullptr) delete item;
    if (ai != nullptr) delete ai;
    if (fighter != nullptr) delete fighter;
    if (glow != nullptr) delete glow;
    if (particleEmitter != nullptr) delete particleEmitter;
    if (player != nullptr) delete player;
};

void Entity::setPos(int x, int y){
    if (this->glow){

    }
    this->posX = x;
    this->posY = y;
}

std::tuple<int,int> Entity::getPos(){
    return {this->posX, this->posY};
}

void Entity::render(){
    Map* map = game->map;
    Tile* tile;
    
    // if (!this->visible) return;
    if (this->fighter && !this->player) if (this->fighter->stealth) return; // dont render fighters under stealth

    if (game->map->inMap(this->posX, this->posY)){
        if ( 
            (this->posY >= map->topSide && this->posY < map->bottomSide) && 
            (this->posX >= map->leftSide && this->posX < map->rightSide)
            ){
            tile = map->tileMap[this->posX][this->posY]; // get tile at entity location for background color matching
        } else return; // out of render area
    } else return; // out of map
    
    // highest dynamic color system
    // short max_color = 0;
    // if (illumination.red > max_color){
    //     max_color = illumination.red;
    // }
    // if (illumination.green > max_color){
    //     max_color = illumination.green;
    // }
    // if (illumination.blue > max_color){
    //     max_color = illumination.blue;
    // }
    // if (max_color > 255){
    //     float ratio = 255.0/max_color;
    //     illumination.red *= ratio;
    //     illumination.green *= ratio;
    //     illumination.blue *= ratio;
    // }
    
    
    if (!game->player->player->canSee(this->posX, this->posY)){
        return; // player can't see this entity
    }

    int screenPosX = this->posX - map->leftSide + map->mapOffsetX;
    int screenPosY = this->posY - map->topSide + map->mapOffsetY;
    map->dest.x = screenPosX * map->tileWidth;
    map->dest.y = screenPosY * map->tileHeight;
    if (this->glow == nullptr){
        // multiply native color by illumination color
        
        
        color lightColored = this->foreRgb;
        /* clearer but less mood
        lightColored.red *= std::min(0.3+this->illumination.red/255.0,1.0);
        lightColored.blue *= std::min(0.3+this->illumination.blue/255.0, 1.0);
        lightColored.green *= std::min(0.3+this->illumination.green/255.0, 1.0);
        */
        lightColored.red *= this->illumination.red/255.0;
        lightColored.green *= this->illumination.green/255.0;
        lightColored.blue *= this->illumination.blue/255.0;
        
        if (this->hasBackground){
            color lightColoredBg = this->backRgb;

            lightColoredBg.red *= this->illumination.red/255.0;
            lightColoredBg.blue *= this->illumination.blue/255.0;
            lightColoredBg.green *= this->illumination.green/255.0;

            int screenPosX = this->posX - map->leftSide + map->mapOffsetX;
            int screenPosY = this->posY - map->topSide + map->mapOffsetY;
            map->dest.x = screenPosX * map->tileWidth;
            map->dest.y = screenPosY * map->tileHeight;

            game->tileManager->drawAscii(
                map->codepage,
                map->src,
                map->dest,
                this->ch,
                lightColored,
                lightColoredBg,
                map->tileHeight, 
                map->tileWidth, 16, 16
            );
        } 
        // items, enemies
        else {
            color lightColoredBg = tile->backRgb; // current tile background color
            
            lightColoredBg.red *= this->illumination.red/255.0;
            lightColoredBg.blue *= this->illumination.blue/255.0;
            lightColoredBg.green *= this->illumination.green/255.0;

            game->tileManager->drawAscii(
            map->codepage,
            map->src,
            map->dest,
            this->ch,
            lightColored, // lightColored for light affected characters
            lightColoredBg,
            map->tileHeight, 
            map->tileWidth, 16, 16);
        }  
    // things which glow:
    } else {
        color lightColoredBg = tile->backRgb; // current tile background color
            
        lightColoredBg.red *= tile->illumination.red/255.0;
        lightColoredBg.blue *= tile->illumination.blue/255.0;
        lightColoredBg.green *= tile->illumination.green/255.0;

        game->tileManager->drawAscii(
            map->codepage,
            map->src,
            map->dest,
            this->ch,
            this->glow->glowColor,
            lightColoredBg,
            map->tileHeight, 
            map->tileWidth, 16, 16);
    }
    
};

void Entity::update(){
    if (!this->glow){
        // list of light sources of the tile = list of light sources of entity
        //this->lightSources = game->map->tileMap[this->posX][this->posY].lightSources;
        this->illumination = game->map->tileMap[this->posX][this->posY]->illumination;
        if (this->illumination.blue+this->illumination.red+this->illumination.green < 60)
            this->visible = false;
        else this->visible = true;
        /*
        short max_color = 0;
        if (illumination.red > max_color){
            max_color = illumination.red;
        }
        if (illumination.green > max_color){
            max_color = illumination.green;
        }
        if (illumination.blue > max_color){
            max_color = illumination.blue;
        }
        float ratio = 255.0/max_color;
        illumination.red *= ratio;
        illumination.green *= ratio;
        illumination.blue *= ratio;*/
        // go through light sources and add all contributions
        /*
        this->illumination = {0,0,0};
        std::list<Entity*>::iterator it;
        for (it=this->lightSources.begin(); it != this->lightSources.end(); it++){
            Glow* light = (*it)->glow;
            shineLight(light->glowColor.red, light->glowColor.green, light->glowColor.blue);
        }*/
    } else {
        // this->glow->clean(this) old light receivers
        // this->glow->update(this);
    }

    if (this->player){
        this->player->updateFov();
    }
    if (this->particleEmitter){
        this->particleEmitter->update();
    }
}

void Entity::shineLight(short red, short green, short blue){
    illumination.red = std::min(255, illumination.red+red);
    illumination.green = std::min(255, illumination.green+green);
    illumination.blue = std::min(255, illumination.blue+blue);
}

void Entity::destroy(){
    this->ch = this->chDestroyed;
    this->foreRgb = this->foreRgbDestroyed;
    if (this->fighter){
        //is in top layer
        game->map->entityList.top.erase(
                std::remove(
                    game->map->entityList.top.begin(),
                    game->map->entityList.top.end(),
                    this
                    )
                );
        
        if (this->inventory.size()==0)
        game->map->entityList.bottom.push_back(this);
        else
        game->map->entityList.mid.push_back(this);
    }
}


bool Entity::pickUp(){
    // picks up item from floor and adds it to inventory, returns true if picked-up something
    // to do: menu to select between items
    std::vector<Entity*>::iterator item;
    item = game->map->entityList.mid.begin();
    while(item != game->map->entityList.mid.end()){
        if ((*item)->item != nullptr){
            if ((*item)->posX == this->posX 
                && (*item)->posY == this->posY){
                if ((*item)->item->pickable) {
                    inventory.push_back(*item);
                    std::cout << "picked up " << (**item).name << std::endl;
                    pickUpAnimation(*item);
                    game->map->entityList.mid.erase(item);
                    return true;
                }
                if(this->player != nullptr
                    && (*item)->inventory.size()>0){
                    std::cout << "open inventory window for chest" << std::endl;
                    game->windows.push_back(new PickupInventoryWindow(*item));
                    return true;
                }
            }
        }
        item++;
    }
    return false;
}

void Entity::drop(Entity* item){
    this->inventory.erase(
        std::remove(
                this->inventory.begin(),
                this->inventory.end(),
                item
            )        
    );
    item->posX = this->posX;
    item->posY = this->posY;
    game->map->entityList.push_back(item);
}

void Entity::removeItem(Entity* item){
    //removes from inventory, leaves hanging pointer
    this->inventory.erase(
        std::remove(
                this->inventory.begin(),
                this->inventory.end(),
                item
            )        
    );
}

void Entity::deleteItem(Entity* item){
    //deletes item data and removes from inventory
    this->inventory.erase(
        std::remove(
                this->inventory.begin(),
                this->inventory.end(),
                item
            )        
    );
    delete item;
}
