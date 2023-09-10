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
    try {
    int x = owner->posX;
    int y = owner->posY;
    int radius = sqrt(intensity/0.05);
    float brightValue = 0;

    std::vector<std::vector <short>> visible = computeFOV(x,y,radius);
    //std::vector<std::vector <bool>> visible = getVisibleRadius(x, y, radius);

    for (float i = -radius; i<=radius; i++){
        for (float j = -radius; j<=radius; j++){
            if (game->map->inMap(x+i, y+j)){
                if (visible[i+radius][j+radius] == 1){
                    brightValue = std::min(float(1), 1/(5*abs(1+i*i+j*j)/intensity) );

                    lightColor* light = &game->map->tileMap[x+i][y+j]->illumination;
                    light->red += short(std::min(float(255-light->red), float(brightValue*this->glowColor.red)));
                    light->green += short(std::min(float(255-light->green), float(brightValue*this->glowColor.green)));
                    light->blue += short(std::min(float(255-light->blue), float(brightValue*this->glowColor.blue) ));
                    // light->red += short(brightValue*this->glowColor.red);
                    // light->green += short(brightValue*this->glowColor.green); 
                    // light->blue += short(brightValue*this->glowColor.blue);
                }
                
           }
        }
    }

    }
    catch(...){
        std::cout<< "Glow::update() error" << std::endl;
    }
}
/*
void Glow::cleanLightReceivers(Entity* owner){
    int x = owner->posX;
    int y = owner->posY;
    // iterate through game entities to find the ones with a reference to this light
    for (Entity* ent : game->map->entityList){
        ent->lightSources.remove(owner);
        ent->update();
    }
    // go through map tiles in range of this light and remove all references to this light
    int radius = sqrt(intensity)*10;
    for (float i = -radius; i<=radius; i++){
        for (float j = -radius; j<=radius; j++){
            if (game->map->inMap(x+i, x+j)){
                game->map->tileMap[x+i][y+i].lightSources.remove(owner);
                game->map->tileMap[x+i][y+i].update();
            }
        }
    }
}*/
