#include "glow.hpp"

#include <algorithm>

#include "entity.hpp"
#include "../game.hpp"
#include "../map.hpp"
#include "../algorithms/fov.hpp"

Glow::Glow(Entity* owner, color glowColor, short intensity){
    this->glowColor = glowColor;
    this->glowOrigColor = glowColor;
    this->intensity = intensity;
    update(owner);
}

void Glow::update(Entity* owner){
    int x = owner->posX;
    int y = owner->posY;
    int radius = sqrt(intensity)*10;
    float brightValue = 0;

    std::vector<std::vector <bool>> visible = getVisibleRadius(x, y, radius);

    for (float i = -radius; i<=radius; i++){
        for (float j = -radius; j<=radius; j++){
            if ( x+i >= 0 && x+i < game->map->mapWidth
             && y+j >= 0 && x+j < game->map->mapHeight){

                if (visible[i+radius][j+radius]){
                    brightValue = std::min(float(1), 1/(abs(1+i*i+j*j)/intensity) );

                    lightColor* light = &game->map->tileMap[x+i][y+j].illumination;
                    light->red += short(std::min(float(255-light->red), float(brightValue*this->glowColor.red)));
                    light->green += short(std::min(float(255-light->green), float(brightValue*this->glowColor.green)));
                    light->blue += short(std::min(float(255-light->blue), float(brightValue*this->glowColor.blue) ));
                }
                
            }
        }
    }
}

void Glow::cleanLightReceivers(Entity* owner){
    int x = owner->posX;
    int y = owner->posY;
    // iterate through game entities to find the ones with a reference to this light
    for (Entity* ent : game->entityList){
        ent->lightSources.remove(owner);
        ent->update();
    }
    // go through map tiles in range of this light and remove all references to this light
    int radius = sqrt(intensity)*10;
    for (float i = -radius; i<=radius; i++){
        for (float j = -radius; j<=radius; j++){
            if ( x+i >= 0 && x+i < game->map->mapWidth
             && y+j >= 0 && x+j < game->map->mapHeight){
                game->map->tileMap[x+i][y+i].lightSources.remove(owner);
                game->map->tileMap[x+i][y+i].update();
            }
        }
    }
}

void Glow::newUpdate(Entity* owner){
    int x = owner->posX;
    int y = owner->posY;


}