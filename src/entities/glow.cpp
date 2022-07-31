#include "glow.hpp"

#include <algorithm>

#include "entity.hpp"
#include "../game.hpp"
#include "../map.hpp"

Glow::Glow(Entity* owner, color glowColor, short intensity){
    this->glowColor = glowColor;
    this->intensity = intensity;
    update(owner);
}

void Glow::update(Entity* owner){
    int x = owner->posX;
    int y = owner->posY;
    int radius = sqrt(intensity)*10;
    float brightValue = 0;
    for (float i = -radius; i<=radius; i++){
        for (float j = -radius; j<=radius; j++){
            if ( x+i >= 0 && x+i < game->map->mapWidth
             && y+j >= 0 && x+j < game->map->mapHeight){
                brightValue = std::min(float(1), 1/(abs(1+i*i+j*j)/intensity) );
                /**
                game->map->tileMap[x+i][y+j].illumination = {
                    short(std::min(float(255), float(brightValue*this->glowColor.red))),
                    short(std::min(float(255), float(brightValue*this->glowColor.green) )),
                    short(std::min(float(255), float(brightValue*this->glowColor.blue) )),
                };**/
                lightColor* light = &game->map->tileMap[x+i][y+j].illumination;
                light->red += short(std::min(float(255-light->red), float(brightValue*this->glowColor.red)));
                light->green += short(std::min(float(255-light->green), float(brightValue*this->glowColor.green)));
                light->blue += short(std::min(float(255-light->blue), float(brightValue*this->glowColor.blue) ));
            }
        }
    }
}