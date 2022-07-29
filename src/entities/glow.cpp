#include "glow.hpp"
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
    int radius = intensity*5;
    float brightValue = 0;
    for (float i = -radius; i<=radius; i++){
        for (float j = -radius; j<=radius; j++){
            if ( x+i >= 0 && x+i < game->map->mapWidth
             && y+j >= 0 && x+j < game->map->mapHeight){
                brightValue = intensity/((1+i*i+j*j));

                game->map->tileMap[x+i][y+j].illumination = {
                    short(brightValue*this->glowColor.red),
                    short(brightValue*this->glowColor.green),
                    short(brightValue*this->glowColor.blue),
                    };
            }
        }
    }
}